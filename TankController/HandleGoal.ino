void HandleGoal(EthernetClient client) {
  PrintHeader(client, 200);

  StaticJsonDocument<200> goal_doc;
  JsonObject goal_obj = goal_doc.to<JsonObject>();

  StaticJsonDocument<100> ph_values_doc;
  JsonArray ph_values = ph_values_doc.to<JsonArray>();
  for (int i = 0; i < ph_series_size; i++) {
    long ph_value_current = ReadLineFromSd("pv.txt", i, GOAL_RECORD_LENGTH);
    ph_values.add(ph_value_current);
  }
  goal_obj["phValues"] = ph_values;

  StaticJsonDocument<100> ph_times_doc;
  JsonArray ph_times = ph_times_doc.to<JsonArray>();
  for (int i = 0; i < ph_series_size; i++) {
    long ph_time_current = ReadLineFromSd("pt.txt", i, GOAL_RECORD_LENGTH);
    ph_times.add(ph_time_current);
  }
  goal_obj["phTimes"] = ph_times;
  goal_obj["phInterval"] = ph_interval;
  goal_obj["phDelay"] = ph_delay;

  StaticJsonDocument<100> temp_values_doc;
  JsonArray temp_values = temp_values_doc.to<JsonArray>();
  for (int i = 0; i < temp_series_size; i++) {
    long temp_value_current = ReadLineFromSd("tv.txt", i, GOAL_RECORD_LENGTH);
    temp_values.add(temp_value_current);
  }
  goal_obj["tempValues"] = temp_values;

  StaticJsonDocument<100> temp_times_doc;
  JsonArray temp_times = temp_times_doc.to<JsonArray>();
  for (int i = 0; i < temp_series_size; i++) {
    long temp_time_current = ReadLineFromSd("tt.txt", i, GOAL_RECORD_LENGTH);
    temp_times.add(temp_time_current);
  }
  goal_obj["tempTimes"] = temp_times;
  goal_obj["tempInterval"] = temp_interval;
  goal_obj["tempDelay"] = temp_delay;

  serializeJson(goal_obj, client);
}
