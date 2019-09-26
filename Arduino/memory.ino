//**************************************************************
//
// Save the Current Positon ant Frequency to the Memory Array
//
//**************************************************************
void saveCurrentMemory() {

  //Save current Frequency position
  if (CURRENT_BAND == BAND_10M) {
    int index = checkIfMemoryExist(memory10m, config.CURRENT_FRQ);
    if (index > -1) {
      memory10m[index].POSITION = config.CURRENT_POSITION;
    } else {
      Memory mem;
      mem.FREQUENCY = config.CURRENT_FRQ;
      mem.POSITION = config.CURRENT_POSITION;
      memory10m[memory10Size] = mem;
      memory10Size = memory10Size + 1;
    }
  } else if (CURRENT_BAND == BAND_12M) {
    int index = checkIfMemoryExist(memory12m, config.CURRENT_FRQ);
    if (index > -1) {
      memory12m[index].POSITION = config.CURRENT_POSITION;
    } else {
      Memory mem;
      mem.FREQUENCY = config.CURRENT_FRQ;
      mem.POSITION = config.CURRENT_POSITION;
      memory12m[memory12Size] = mem;
      memory12Size = memory12Size + 1;
    }
  } else if (CURRENT_BAND == BAND_15M) {
    int index = checkIfMemoryExist(memory15m, config.CURRENT_FRQ);
    if (index > -1) {
      memory15m[index].POSITION = config.CURRENT_POSITION;
    } else {
      Memory mem;
      mem.FREQUENCY = config.CURRENT_FRQ;
      mem.POSITION = config.CURRENT_POSITION;
      memory15m[memory15Size] = mem;
      memory15Size = memory15Size + 1;
    }
  } else if (CURRENT_BAND == BAND_17M) {
    int index = checkIfMemoryExist(memory17m, config.CURRENT_FRQ);
    if (index > -1) {
      memory17m[index].POSITION = config.CURRENT_POSITION;
    } else {
      Memory mem;
      mem.FREQUENCY = config.CURRENT_FRQ;
      mem.POSITION = config.CURRENT_POSITION;
      memory17m[memory17Size] = mem;
      memory17Size = memory17Size + 1;
    }
  } else if (CURRENT_BAND == BAND_20M) {
    int index = checkIfMemoryExist(memory20m, config.CURRENT_FRQ);
    if (index > -1) {
      memory20m[index].POSITION = config.CURRENT_POSITION;
    } else {
      Memory mem;
      mem.FREQUENCY = config.CURRENT_FRQ;
      mem.POSITION = config.CURRENT_POSITION;
      memory20m[memory20Size] = mem;
      memory20Size = memory20Size + 1;
    }
  } else  if (CURRENT_BAND == BAND_30M) {
    int index = checkIfMemoryExist(memory30m, config.CURRENT_FRQ);
    if (index > -1) {
      memory30m[index].POSITION = config.CURRENT_POSITION;
    } else {
      Memory mem;
      mem.FREQUENCY = config.CURRENT_FRQ;
      mem.POSITION = config.CURRENT_POSITION;
      memory30m[memory30Size] = mem;
      memory30Size = memory30Size + 1;
    }
  } else if (CURRENT_BAND == BAND_40M) {
    int index = checkIfMemoryExist(memory40m, config.CURRENT_FRQ);
    if (index > -1) {
      memory40m[index].POSITION = config.CURRENT_POSITION;
    } else {
      Memory mem;
      mem.FREQUENCY = config.CURRENT_FRQ;
      mem.POSITION = config.CURRENT_POSITION;
      memory40m[memory40Size] = mem;
      memory40Size = memory40Size + 1;
    }
  } else if (CURRENT_BAND == BAND_60M) {
    int index = checkIfMemoryExist(memory60m, config.CURRENT_FRQ);
    if (index > -1) {
      memory60m[index].POSITION = config.CURRENT_POSITION;
    } else {
      Memory mem;
      mem.FREQUENCY = config.CURRENT_FRQ;
      mem.POSITION = config.CURRENT_POSITION;
      memory60m[memory60Size] = mem;
      memory60Size = memory60Size + 1;
    }
  } else if (CURRENT_BAND == BAND_80M) {
    int index = checkIfMemoryExist(memory80m, config.CURRENT_FRQ);
    if (index > -1) {
      memory80m[index].POSITION = config.CURRENT_POSITION;
    } else {
      Memory mem;
      mem.FREQUENCY = config.CURRENT_FRQ;
      mem.POSITION = config.CURRENT_POSITION;
      memory80m[memory80Size] = mem;
      memory80Size = memory80Size + 1;
    }
  } else if (CURRENT_BAND == BAND_160M) {
    int index = checkIfMemoryExist(memory160m, config.CURRENT_FRQ);
    if (index > -1) {
      memory160m[index].POSITION = config.CURRENT_POSITION;
    } else {
      Memory mem;
      mem.FREQUENCY = config.CURRENT_FRQ;
      mem.POSITION = config.CURRENT_POSITION;
      memory160m[memory160Size] = mem;
      memory160Size = memory160Size + 1;
    }
  }
  startSaveMemory();
}
//********************************************************************************
//
//      Check if the current frenquency has been already saved in the memory
//
//********************************************************************************
int checkIfMemoryExist(Memory mem[], uint32_t frequency) {
  int exist = -1;
  for (int x = 0; x < MEMORY_MAX_SIZE; x++) {
    if (mem[x].FREQUENCY == frequency) {
      exist = x;
      break;
    }
  }
  return exist;
}
//********************************************************************************
//
//      Get Memory Position
//
//********************************************************************************
uint32_t getMemoryPosition( uint32_t frequency) {
  uint32_t position = config.CURRENT_POSITION;
  for (int x = 0; x < MEMORY_MAX_SIZE; x++) {
    #ifdef ANTENNA_BAND_10M
    if (CURRENT_BAND == BAND_10M && memory10m[x].FREQUENCY == frequency) {
        position = memory10m[x].POSITION;
        break;
    }
    #endif
    #ifdef ANTENNA_BAND_12M
    if (CURRENT_BAND == BAND_12M && memory12m[x].FREQUENCY == frequency) {
        position = memory12m[x].POSITION;
        break;
    }
    #endif
    #ifdef ANTENNA_BAND_15M
    if (CURRENT_BAND == BAND_15M && memory15m[x].FREQUENCY == frequency) {
        position = memory15m[x].POSITION;
        break;
    }
    #endif
    #ifdef ANTENNA_BAND_17M
    if (CURRENT_BAND == BAND_17M && memory17m[x].FREQUENCY == frequency) {
        position = memory17m[x].POSITION;
        break;
    }
    #endif
    #ifdef ANTENNA_BAND_20M
    if (CURRENT_BAND == BAND_20M && memory20m[x].FREQUENCY == frequency) {
        position = memory20m[x].POSITION;
        break;
    }
    #endif
    #ifdef ANTENNA_BAND_30M
    if (CURRENT_BAND == BAND_30M && memory30m[x].FREQUENCY == frequency) {
        position = memory30m[x].POSITION;
        break;
    }
    #endif
    #ifdef ANTENNA_BAND_40M
    if (CURRENT_BAND == BAND_40M && memory40m[x].FREQUENCY == frequency) {
        position = memory40m[x].POSITION;
        break;
    }
    #endif
    #ifdef ANTENNA_BAND_60M
    if (CURRENT_BAND == BAND_60M && memory60m[x].FREQUENCY == frequency) {
        position = memory60m[x].POSITION;
        break;
    }
    #endif
    #ifdef ANTENNA_BAND_80M
    if (CURRENT_BAND == BAND_80M && memory80m[x].FREQUENCY == frequency) {
        position = memory80m[x].POSITION;
        break;
    }
    #endif
    #ifdef ANTENNA_BAND_160M
    if (CURRENT_BAND == BAND_160M && memory160m[x].FREQUENCY == frequency) {
        position = memory160m[x].POSITION;
        break;
    }
    #endif
  }
  #ifdef DEBUG
  Serial.println("CURRENT_BAND");
  Serial.println(CURRENT_BAND);
  Serial.println("CURRENT_MODE");
  Serial.println(CURRENT_MODE);
  Serial.println("Frequency");
  Serial.println(frequency);
  Serial.println("Position");
  Serial.println(position);
  Serial.println("Current Position");
  Serial.println(config.CURRENT_POSITION);
  #endif
  return position;
}
//***********************************************
//
//     Converts memory arroy to json object
//
//***********************************************
void memoryToJson( int band) {

  StaticJsonDocument<2512> doc;
  // Set the values in the document

  if (band == BAND_10M) {
    doc["memorySize10m"] = memory10Size;
    for (int x = 0; x < MEMORY_MAX_SIZE; x++) {
      doc["memory10m"][String(x)]["FREQUENCY"] = memory10m[x].FREQUENCY;
      doc["memory10m"][String(x)]["POSITION"] = memory10m[x].POSITION;
      delay(10);
    }
  } else if (band == BAND_12M) {
    doc["memorySize12m"] = memory12Size;
    for (int x = 0; x < MEMORY_MAX_SIZE; x++) {
      doc["memory12m"][String(x)]["FREQUENCY"] = memory12m[x].FREQUENCY;
      doc["memory12m"][String(x)]["POSITION"] = memory12m[x].POSITION;
      delay(10);
    }
  } else if (band == BAND_15M) {
    doc["memorySize15m"] = memory15Size;
    for (int x = 0; x < MEMORY_MAX_SIZE; x++) {
      doc["memory15m"][String(x)]["FREQUENCY"] = memory15m[x].FREQUENCY;
      doc["memory15m"][String(x)]["POSITION"] = memory15m[x].POSITION;
      delay(10);
    }
  } else if (band == BAND_17M) {
    doc["memorySize17m"] = memory17Size;
    for (int x = 0; x < MEMORY_MAX_SIZE; x++) {
      doc["memory17m"][String(x)]["FREQUENCY"] = memory17m[x].FREQUENCY;
      doc["memory17m"][String(x)]["POSITION"] = memory17m[x].POSITION;
      delay(10);
    }
  } else if (band == BAND_20M) {
    doc["memorySize20m"] = memory20Size;
    for (int x = 0; x < MEMORY_MAX_SIZE; x++) {
      doc["memory20m"][String(x)]["FREQUENCY"] = memory20m[x].FREQUENCY;
      doc["memory20m"][String(x)]["POSITION"] = memory20m[x].POSITION;
      delay(10);
    }
  } else if (band == BAND_30M) {
    doc["memorySize30m"] = memory30Size;
    for (int x = 0; x < MEMORY_MAX_SIZE; x++) {
      doc["memory30m"][String(x)]["FREQUENCY"] = memory30m[x].FREQUENCY;
      doc["memory30m"][String(x)]["POSITION"] = memory30m[x].POSITION;
      delay(10);
    }
  } else if (band == BAND_40M) {
    doc["memorySize40m"] = memory40Size;
    for (int x = 0; x < MEMORY_MAX_SIZE; x++) {
      doc["memory40m"][String(x)]["FREQUENCY"] = memory40m[x].FREQUENCY;
      doc["memory40m"][String(x)]["POSITION"] = memory40m[x].POSITION;
      delay(10);
    }
  } else if (band == BAND_60M) {
    doc["memorySize60m"] = memory60Size;
    for (int x = 0; x < MEMORY_MAX_SIZE; x++) {
      doc["memory60m"][String(x)]["FREQUENCY"] = memory60m[x].FREQUENCY;
      doc["memory60m"][String(x)]["POSITION"] = memory60m[x].POSITION;
      delay(10);
    }
  } else if (band == BAND_80M) {
    doc["memorySize80m"] = memory20Size;
    for (int x = 0; x < MEMORY_MAX_SIZE; x++) {
      doc["memory80m"][String(x)]["FREQUENCY"] = memory80m[x].FREQUENCY;
      doc["memory80m"][String(x)]["POSITION"] = memory80m[x].POSITION;
      delay(10);
    }
  } else if (band == BAND_160M) {
    doc["memorySize160m"] = memory160Size;
    for (int x = 0; x < MEMORY_MAX_SIZE; x++) {
      doc["memory160m"][String(x)]["FREQUENCY"] = memory160m[x].FREQUENCY;
      doc["memory160m"][String(x)]["POSITION"] = memory160m[x].POSITION;
      delay(10);
    }
  }
  return doc;
}
//*************************************************************
//
//      Start the timeout cycle to save memories to sd card
//
//*************************************************************
void startSaveMemory() {
  MEM_STATUS = PROCESSING;
  toSavedMem = true;
  toSavedMemTimeoutCycle = 0;
}
//*************************************************************************
//
//      Check if the current frequency has been saved to the memories
//        and if the current possition is tuned to the frequency
//
//************************************************************************

void checkMemories() {
  toTunedPosition = -1;
  uint32_t modeOffset = getModePositionOffset();
  TUNED_STATUS = STATUS_ERROR;
  for (int x = 0; x < MEMORY_MAX_SIZE; x++) {
    if (CURRENT_BAND == BAND_10M) {
      if (memory10m[x].FREQUENCY == config.CURRENT_FRQ) {
        if (memory10m[x].POSITION + modeOffset == config.CURRENT_POSITION ) {
          TUNED_STATUS = OK;
          toTunedPositionTimeoutCycle = 0;
          toTunedPositionChange = false;
          toTunedPosition = 0;
        } else {
          TUNED_STATUS = WRONG_POSITION;
          toTunedPosition = memory10m[x].POSITION + modeOffset;
          toTunedPositionChange = true;
        }
        break;
      }
    } else if (CURRENT_BAND == BAND_12M) {
      if (memory12m[x].FREQUENCY == config.CURRENT_FRQ) {
        if (memory12m[x].POSITION + modeOffset == config.CURRENT_POSITION ) {
          TUNED_STATUS = OK;
          toTunedPositionTimeoutCycle = 0;
          toTunedPositionChange = false;
          toTunedPosition = 0;
        } else {
          TUNED_STATUS = WRONG_POSITION;
          toTunedPosition = memory12m[x].POSITION + modeOffset;
          toTunedPositionChange = true;
        }
        break;
      }
    } else if (CURRENT_BAND == BAND_15M) {
      if (memory15m[x].FREQUENCY == config.CURRENT_FRQ) {
        if (memory15m[x].POSITION + modeOffset == config.CURRENT_POSITION ) {
          TUNED_STATUS = OK;
          toTunedPositionTimeoutCycle = 0;
          toTunedPositionChange = false;
          toTunedPosition = 0;
        } else {
          TUNED_STATUS = WRONG_POSITION;
          toTunedPosition = memory15m[x].POSITION + modeOffset;
          toTunedPositionChange = true;
        }
        break;
      }
    } else if (CURRENT_BAND == BAND_17M) {
      if (memory17m[x].FREQUENCY == config.CURRENT_FRQ) {
        if (memory17m[x].POSITION + modeOffset == config.CURRENT_POSITION ) {
          TUNED_STATUS = OK;
          toTunedPositionTimeoutCycle = 0;
          toTunedPositionChange = false;
          toTunedPosition = 0;
        } else {
          TUNED_STATUS = WRONG_POSITION;
          toTunedPosition = memory17m[x].POSITION + modeOffset;
          toTunedPositionChange = true;
        }
        break;
      }
    } else if (CURRENT_BAND == BAND_20M) {
      if (memory20m[x].FREQUENCY == config.CURRENT_FRQ) {
        if (memory20m[x].POSITION + modeOffset == config.CURRENT_POSITION ) {
          TUNED_STATUS = OK;
          toTunedPositionTimeoutCycle = 0;
          toTunedPositionChange = false;
          toTunedPosition = 0;
        } else {
          TUNED_STATUS = WRONG_POSITION;
          toTunedPosition = memory20m[x].POSITION + modeOffset;
          toTunedPositionChange = true;
        }
        break;
      }
    } else  if (CURRENT_BAND == BAND_30M) {
      if (memory30m[x].FREQUENCY == config.CURRENT_FRQ) {
        if (memory30m[x].POSITION + modeOffset == config.CURRENT_POSITION) {
          TUNED_STATUS = OK;
          toTunedPositionTimeoutCycle = 0;
          toTunedPositionChange = false;
          toTunedPosition = 0;
        } else {
          TUNED_STATUS = WRONG_POSITION;
          toTunedPosition = memory30m[x].POSITION + modeOffset;
          toTunedPositionChange = true;
        }
        break;
      }
    } else if (CURRENT_BAND == BAND_40M) {
      if (memory40m[x].FREQUENCY == config.CURRENT_FRQ) {
        if (memory40m[x].POSITION + modeOffset == config.CURRENT_POSITION) {
          TUNED_STATUS = OK;
          toTunedPositionTimeoutCycle = 0;
          toTunedPositionChange = false;
          toTunedPosition = 0;
        } else {
          TUNED_STATUS = WRONG_POSITION;
          toTunedPosition = memory40m[x].POSITION + modeOffset;
          toTunedPositionChange = true;
        }
        break;
      }
    } else if (CURRENT_BAND == BAND_60M) {
      if (memory60m[x].FREQUENCY == config.CURRENT_FRQ) {
        if (memory60m[x].POSITION + modeOffset == config.CURRENT_POSITION) {
          TUNED_STATUS = OK;
          toTunedPositionTimeoutCycle = 0;
          toTunedPositionChange = false;
          toTunedPosition = 0;
        } else {
          TUNED_STATUS = WRONG_POSITION;
          toTunedPosition = memory60m[x].POSITION + modeOffset;
          toTunedPositionChange = true;
        }
        break;
      }
    } else if (CURRENT_BAND == BAND_80M) {
      if (memory80m[x].FREQUENCY == config.CURRENT_FRQ) {
        if (memory80m[x].POSITION + modeOffset == config.CURRENT_POSITION) {
          TUNED_STATUS = OK;
          toTunedPositionTimeoutCycle = 0;
          toTunedPositionChange = false;
          toTunedPosition = 0;
        } else {
          TUNED_STATUS = WRONG_POSITION;
          toTunedPosition = memory80m[x].POSITION + modeOffset;
          toTunedPositionChange = true;
        }
        break;
      }
    } else if (CURRENT_BAND == BAND_160M) {
      if (memory160m[x].FREQUENCY == config.CURRENT_FRQ) {
        if (memory160m[x].POSITION + modeOffset == config.CURRENT_POSITION ) {
          TUNED_STATUS = OK;
          toTunedPositionTimeoutCycle = 0;
          toTunedPositionChange = false;
          toTunedPosition = 0;
        } else {
          TUNED_STATUS = WRONG_POSITION;
          toTunedPosition = memory160m[x].POSITION + modeOffset;
          toTunedPositionChange = true;
        }
        break;
      }
    }
  }
}
