// ENERGY METER AND BUTTON STATUS:
function Decoder(bytes, port) {
    if (bytes.length == 1) {
        if (bytes[0] == 1) {
            return {
                'Button' : 'Activated'
            }
        } else {
            return {
                'Error' : 'Unknown button action'
            }
        }
    } else if (bytes.length > 1) {

        //        *  Voltage       (Volts)   --> ( response[3]   << 8 | response[4] )  / 10.0 )
        //        *  Current       (Amperes) --> ( response[5]   << 8 | response[6]    | response[7]  << 24 | response[8]  << 16 ) / 1000.0 )
        //        *  Power         (Watts)   --> ( response[9]   << 8 | response[10]   | response[11] << 24 | response[12] << 16 ) / 10.0 )
        //        *  Energy        (kWh)     --> ( response[13]  << 8 | response[14]   | response[15] << 24 | response[16] << 16 ) / 1000.0 )
        //        *  Frequency     (Hz)      --> ( response[17]  << 8 | response[18] ) / 10.0 )
        //        *  Power Factor  (.)       --> ( response[19]  << 8 | response[20] ) / 100.0 )
        //        *  Alarm         (.)       --> ( response[21]  << 8 | response[22] ) )
        
        var voltagePhaseA         = ( ( bytes[3]   << 8 | bytes[4] ) );
        var currentPhaseA         = ( ( bytes[5]   << 8 | bytes[6]    | bytes[7]  << 24 | bytes[8]  << 16 ) );
        var powerPhaseA           = ( ( bytes[9]   << 8 | bytes[10]   | bytes[11] << 24 | bytes[12] << 16 ) );
        var energyPhaseA          = ( ( bytes[13]  << 8 | bytes[14]   | bytes[15] << 24 | bytes[16] << 16 ) );
        var frequencyPhaseA       = ( ( bytes[17]  << 8 | bytes[18] ) );
        var powerFactorPhaseA     = ( ( bytes[19]  << 8 | bytes[20] ) );
        var alarmPhaseA           = ( ( bytes[21]  << 8 | bytes[22] ) );
        
        var voltagePhaseB         = ( ( bytes[3 + 25]   << 8 | bytes[4 + 25] ) );
        var currentPhaseB         = ( ( bytes[5 + 25]   << 8 | bytes[6 + 25]    | bytes[7 + 25]  << 24 | bytes[8 + 25]  << 16 ) );
        var powerPhaseB           = ( ( bytes[9 + 25]   << 8 | bytes[10 + 25]   | bytes[11 + 25] << 24 | bytes[12 + 25] << 16 ) );
        var energyPhaseB          = ( ( bytes[13 + 25]  << 8 | bytes[14 + 25]   | bytes[15 + 25] << 24 | bytes[16 + 25] << 16 ) );
        var frequencyPhaseB       = ( ( bytes[17 + 25]  << 8 | bytes[18 + 25] ) );
        var powerFactorPhaseB     = ( ( bytes[19 + 25]  << 8 | bytes[20 + 25] ) );
        var alarmPhaseB           = ( ( bytes[21 + 25]  << 8 | bytes[22 + 25] ) );
        
        var voltagePhaseC         = ( ( bytes[3 + 50]   << 8 | bytes[4 + 50] )  );
        var currentPhaseC         = ( ( bytes[5 + 50]   << 8 | bytes[6 + 50]    | bytes[7 + 50]  << 24 | bytes[8 + 50]  << 16 ) );
        var powerPhaseC           = ( ( bytes[9 + 50]   << 8 | bytes[10 + 50]   | bytes[11 + 50] << 24 | bytes[12 + 50] << 16 ) );
        var energyPhaseC          = ( ( bytes[13 + 50]  << 8 | bytes[14 + 50]   | bytes[15 + 50] << 24 | bytes[16 + 50] << 16 ) );
        var frequencyPhaseC       = ( ( bytes[17 + 50]  << 8 | bytes[18 + 50] ) );
        var powerFactorPhaseC     = ( ( bytes[19 + 50]  << 8 | bytes[20 + 50] ) );
        var alarmPhaseC           = ( ( bytes[21 + 50]  << 8 | bytes[22 + 50] ) );

        decodedVoltagePhaseA     = voltagePhaseA	/ 10.0;
        decodedCurrentPhaseA     = currentPhaseA	/ 1000.0;
        decodedPowerPhaseA       = powerPhaseA		/ 10.0;
        decodedEnergyPhaseA      = energyPhaseA		/ 1000.0;
        decodedFrequencyPhaseA   = frequencyPhaseA	/ 10.0;
        decodedPowerFactorPhaseA = powerFactorPhaseA	/ 100.0;
        decodedAlarmPhaseA       = alarmPhaseA;
        
        decodedVoltagePhaseB     = voltagePhaseB	/ 10.0;
        decodedCurrentPhaseB     = currentPhaseB	/ 1000.0;
        decodedPowerPhaseB       = powerPhaseB		/ 10.0;
        decodedEnergyPhaseB      = energyPhaseB		/ 1000.0;
        decodedFrequencyPhaseB   = frequencyPhaseB	/ 10.0;
        decodedPowerFactorPhaseB = powerFactorPhaseB	/ 100.0;
        decodedAlarmPhaseB       = alarmPhaseB;
        
        decodedVoltagePhaseC     = voltagePhaseC	/ 10.0;
        decodedCurrentPhaseC     = currentPhaseC	/ 1000.0;
        decodedPowerPhaseC       = powerPhaseC		/ 10.0;
        decodedEnergyPhaseC      = energyPhaseC		/ 1000.0;
        decodedFrequencyPhaseC   = frequencyPhaseC	/ 10.0;
        decodedPowerFactorPhaseC = powerFactorPhaseC	/ 100.0;
        decodedAlarmPhaseC       = alarmPhaseC;        
        
        return {        
	    'voltagePhaseA'     : decodedVoltagePhaseA,
	    'currentPhaseA'     : decodedCurrentPhaseA,
	    'powerPhaseA'       : decodedPowerPhaseA,
	    'energyPhaseA'      : decodedEnergyPhaseA,
	    'frequencyPhaseA'   : decodedFrequencyPhaseA,
	    'powerFactorPhaseA' : decodedPowerFactorPhaseA,
	    'alarmPhaseA'       : decodedAlarmPhaseA,
    	    'voltagePhaseB'     : decodedVoltagePhaseB,
	    'currentPhaseB'     : decodedCurrentPhaseB,
	    'powerPhaseB'       : decodedPowerPhaseB,
	    'energyPhaseB'      : decodedEnergyPhaseB,
	    'frequencyPhaseB'   : decodedFrequencyPhaseB,
	    'powerFactorPhaseB' : decodedPowerFactorPhaseB,
	    'alarmPhaseB'       : decodedAlarmPhaseB,
    	    'voltagePhaseC'     : decodedVoltagePhaseC,
	    'currentPhaseC'     : decodedCurrentPhaseC,
	    'powerPhaseC'       : decodedPowerPhaseC,
	    'energyPhaseC'      : decodedEnergyPhaseC,
	    'frequencyPhaseC'   : decodedFrequencyPhaseC,
	    'powerFactorPhaseC' : decodedPowerFactorPhaseC,
	    'alarmPhaseC'       : decodedAlarmPhaseC
        }
    } else {
        return {
            'Error': 'Unknown payload'
        }
    }
}

// PAYLOAD TEST:
// --> Data of PZEM to send
//01 04 14 08 9a 00 29 00 00 00 12 00 00 00 ed 00 00 02 57 00 14 00 00 51 38

//  --> Data of PZEM to send
//02 04 14 08 9a 00 27 00 00 00 06 00 00 00 01 00 00 02 57 00 07 00 00 3c ab

// --> Data of PZEM to send
//03 04 14 08 9b 00 29 00 00 00 07 00 00 00 35 00 00 02 57 00 08 00 00 fc eb

// --> FULL Data of PZEM to send
// 01 04 14 08 9a 00 29 00 00 00 12 00 00 00 ed 00 00 02 57 00 14 00 00 51 38 02 04 14 08 9a 00 27 00 00 00 06 00 00 00 01 00 00 02 57 00 07 00 00 3c ab 03 04 14 08 9b 00 29 00 00 00 07 00 00 00 35 00 00 02 57 00 08 00 00 fc eb
