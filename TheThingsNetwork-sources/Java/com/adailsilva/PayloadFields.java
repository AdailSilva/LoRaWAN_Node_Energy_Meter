package com.adailsilva;

import java.util.HashMap;
import java.util.Map;
import com.fasterxml.jackson.annotation.JsonAnyGetter;
import com.fasterxml.jackson.annotation.JsonAnySetter;
import com.fasterxml.jackson.annotation.JsonIgnore;
import com.fasterxml.jackson.annotation.JsonInclude;
import com.fasterxml.jackson.annotation.JsonProperty;
import com.fasterxml.jackson.annotation.JsonPropertyOrder;
import org.apache.commons.lang.builder.EqualsBuilder;
import org.apache.commons.lang.builder.HashCodeBuilder;
import org.apache.commons.lang.builder.ToStringBuilder;

@JsonInclude(JsonInclude.Include.NON_NULL)
@JsonPropertyOrder({
    "Alarm_Phase_A",
    "Alarm_Phase_B",
    "Alarm_Phase_C",
    "Current_Phase_A",
    "Current_Phase_B",
    "Current_Phase_C",
    "Energy_Phase_A",
    "Energy_Phase_B",
    "Energy_Phase_C",
    "Frequency_Phase_A",
    "Frequency_Phase_B",
    "Frequency_Phase_C",
    "PowerFactor_Phase_A",
    "PowerFactor_Phase_B",
    "PowerFactor_Phase_C",
    "Power_Phase_A",
    "Power_Phase_B",
    "Power_Phase_C",
    "Voltage_Phase_A",
    "Voltage_Phase_B",
    "Voltage_Phase_C"
})
public class PayloadFields {

    @JsonProperty("Alarm_Phase_A")
    private Long alarmPhaseA;
    @JsonProperty("Alarm_Phase_B")
    private Long alarmPhaseB;
    @JsonProperty("Alarm_Phase_C")
    private Long alarmPhaseC;
    @JsonProperty("Current_Phase_A")
    private Double currentPhaseA;
    @JsonProperty("Current_Phase_B")
    private Double currentPhaseB;
    @JsonProperty("Current_Phase_C")
    private Double currentPhaseC;
    @JsonProperty("Energy_Phase_A")
    private Double energyPhaseA;
    @JsonProperty("Energy_Phase_B")
    private Double energyPhaseB;
    @JsonProperty("Energy_Phase_C")
    private Double energyPhaseC;
    @JsonProperty("Frequency_Phase_A")
    private Long frequencyPhaseA;
    @JsonProperty("Frequency_Phase_B")
    private Long frequencyPhaseB;
    @JsonProperty("Frequency_Phase_C")
    private Long frequencyPhaseC;
    @JsonProperty("PowerFactor_Phase_A")
    private Double powerFactorPhaseA;
    @JsonProperty("PowerFactor_Phase_B")
    private Double powerFactorPhaseB;
    @JsonProperty("PowerFactor_Phase_C")
    private Double powerFactorPhaseC;
    @JsonProperty("Power_Phase_A")
    private Double powerPhaseA;
    @JsonProperty("Power_Phase_B")
    private Double powerPhaseB;
    @JsonProperty("Power_Phase_C")
    private Double powerPhaseC;
    @JsonProperty("Voltage_Phase_A")
    private Long voltagePhaseA;
    @JsonProperty("Voltage_Phase_B")
    private Double voltagePhaseB;
    @JsonProperty("Voltage_Phase_C")
    private Double voltagePhaseC;
    @JsonIgnore
    private Map<String, Object> additionalProperties = new HashMap<String, Object>();

    /**
     * No args constructor for use in serialization
     * 
     */
    public PayloadFields() {
    }

    /**
     * 
     * @param frequencyPhaseC
     * @param currentPhaseC
     * @param frequencyPhaseA
     * @param currentPhaseB
     * @param frequencyPhaseB
     * @param energyPhaseA
     * @param energyPhaseB
     * @param alarmPhaseC
     * @param voltagePhaseB
     * @param alarmPhaseB
     * @param voltagePhaseA
     * @param powerPhaseB
     * @param powerPhaseC
     * @param voltagePhaseC
     * @param energyPhaseC
     * @param powerPhaseA
     * @param currentPhaseA
     * @param powerFactorPhaseA
     * @param powerFactorPhaseB
     * @param powerFactorPhaseC
     * @param alarmPhaseA
     */
    public PayloadFields(Long alarmPhaseA, Long alarmPhaseB, Long alarmPhaseC, Double currentPhaseA, Double currentPhaseB, Double currentPhaseC, Double energyPhaseA, Double energyPhaseB, Double energyPhaseC, Long frequencyPhaseA, Long frequencyPhaseB, Long frequencyPhaseC, Double powerFactorPhaseA, Double powerFactorPhaseB, Double powerFactorPhaseC, Double powerPhaseA, Double powerPhaseB, Double powerPhaseC, Long voltagePhaseA, Double voltagePhaseB, Double voltagePhaseC) {
        super();
        this.alarmPhaseA = alarmPhaseA;
        this.alarmPhaseB = alarmPhaseB;
        this.alarmPhaseC = alarmPhaseC;
        this.currentPhaseA = currentPhaseA;
        this.currentPhaseB = currentPhaseB;
        this.currentPhaseC = currentPhaseC;
        this.energyPhaseA = energyPhaseA;
        this.energyPhaseB = energyPhaseB;
        this.energyPhaseC = energyPhaseC;
        this.frequencyPhaseA = frequencyPhaseA;
        this.frequencyPhaseB = frequencyPhaseB;
        this.frequencyPhaseC = frequencyPhaseC;
        this.powerFactorPhaseA = powerFactorPhaseA;
        this.powerFactorPhaseB = powerFactorPhaseB;
        this.powerFactorPhaseC = powerFactorPhaseC;
        this.powerPhaseA = powerPhaseA;
        this.powerPhaseB = powerPhaseB;
        this.powerPhaseC = powerPhaseC;
        this.voltagePhaseA = voltagePhaseA;
        this.voltagePhaseB = voltagePhaseB;
        this.voltagePhaseC = voltagePhaseC;
    }

    @JsonProperty("Alarm_Phase_A")
    public Long getAlarmPhaseA() {
        return alarmPhaseA;
    }

    @JsonProperty("Alarm_Phase_A")
    public void setAlarmPhaseA(Long alarmPhaseA) {
        this.alarmPhaseA = alarmPhaseA;
    }

    @JsonProperty("Alarm_Phase_B")
    public Long getAlarmPhaseB() {
        return alarmPhaseB;
    }

    @JsonProperty("Alarm_Phase_B")
    public void setAlarmPhaseB(Long alarmPhaseB) {
        this.alarmPhaseB = alarmPhaseB;
    }

    @JsonProperty("Alarm_Phase_C")
    public Long getAlarmPhaseC() {
        return alarmPhaseC;
    }

    @JsonProperty("Alarm_Phase_C")
    public void setAlarmPhaseC(Long alarmPhaseC) {
        this.alarmPhaseC = alarmPhaseC;
    }

    @JsonProperty("Current_Phase_A")
    public Double getCurrentPhaseA() {
        return currentPhaseA;
    }

    @JsonProperty("Current_Phase_A")
    public void setCurrentPhaseA(Double currentPhaseA) {
        this.currentPhaseA = currentPhaseA;
    }

    @JsonProperty("Current_Phase_B")
    public Double getCurrentPhaseB() {
        return currentPhaseB;
    }

    @JsonProperty("Current_Phase_B")
    public void setCurrentPhaseB(Double currentPhaseB) {
        this.currentPhaseB = currentPhaseB;
    }

    @JsonProperty("Current_Phase_C")
    public Double getCurrentPhaseC() {
        return currentPhaseC;
    }

    @JsonProperty("Current_Phase_C")
    public void setCurrentPhaseC(Double currentPhaseC) {
        this.currentPhaseC = currentPhaseC;
    }

    @JsonProperty("Energy_Phase_A")
    public Double getEnergyPhaseA() {
        return energyPhaseA;
    }

    @JsonProperty("Energy_Phase_A")
    public void setEnergyPhaseA(Double energyPhaseA) {
        this.energyPhaseA = energyPhaseA;
    }

    @JsonProperty("Energy_Phase_B")
    public Double getEnergyPhaseB() {
        return energyPhaseB;
    }

    @JsonProperty("Energy_Phase_B")
    public void setEnergyPhaseB(Double energyPhaseB) {
        this.energyPhaseB = energyPhaseB;
    }

    @JsonProperty("Energy_Phase_C")
    public Double getEnergyPhaseC() {
        return energyPhaseC;
    }

    @JsonProperty("Energy_Phase_C")
    public void setEnergyPhaseC(Double energyPhaseC) {
        this.energyPhaseC = energyPhaseC;
    }

    @JsonProperty("Frequency_Phase_A")
    public Long getFrequencyPhaseA() {
        return frequencyPhaseA;
    }

    @JsonProperty("Frequency_Phase_A")
    public void setFrequencyPhaseA(Long frequencyPhaseA) {
        this.frequencyPhaseA = frequencyPhaseA;
    }

    @JsonProperty("Frequency_Phase_B")
    public Long getFrequencyPhaseB() {
        return frequencyPhaseB;
    }

    @JsonProperty("Frequency_Phase_B")
    public void setFrequencyPhaseB(Long frequencyPhaseB) {
        this.frequencyPhaseB = frequencyPhaseB;
    }

    @JsonProperty("Frequency_Phase_C")
    public Long getFrequencyPhaseC() {
        return frequencyPhaseC;
    }

    @JsonProperty("Frequency_Phase_C")
    public void setFrequencyPhaseC(Long frequencyPhaseC) {
        this.frequencyPhaseC = frequencyPhaseC;
    }

    @JsonProperty("PowerFactor_Phase_A")
    public Double getPowerFactorPhaseA() {
        return powerFactorPhaseA;
    }

    @JsonProperty("PowerFactor_Phase_A")
    public void setPowerFactorPhaseA(Double powerFactorPhaseA) {
        this.powerFactorPhaseA = powerFactorPhaseA;
    }

    @JsonProperty("PowerFactor_Phase_B")
    public Double getPowerFactorPhaseB() {
        return powerFactorPhaseB;
    }

    @JsonProperty("PowerFactor_Phase_B")
    public void setPowerFactorPhaseB(Double powerFactorPhaseB) {
        this.powerFactorPhaseB = powerFactorPhaseB;
    }

    @JsonProperty("PowerFactor_Phase_C")
    public Double getPowerFactorPhaseC() {
        return powerFactorPhaseC;
    }

    @JsonProperty("PowerFactor_Phase_C")
    public void setPowerFactorPhaseC(Double powerFactorPhaseC) {
        this.powerFactorPhaseC = powerFactorPhaseC;
    }

    @JsonProperty("Power_Phase_A")
    public Double getPowerPhaseA() {
        return powerPhaseA;
    }

    @JsonProperty("Power_Phase_A")
    public void setPowerPhaseA(Double powerPhaseA) {
        this.powerPhaseA = powerPhaseA;
    }

    @JsonProperty("Power_Phase_B")
    public Double getPowerPhaseB() {
        return powerPhaseB;
    }

    @JsonProperty("Power_Phase_B")
    public void setPowerPhaseB(Double powerPhaseB) {
        this.powerPhaseB = powerPhaseB;
    }

    @JsonProperty("Power_Phase_C")
    public Double getPowerPhaseC() {
        return powerPhaseC;
    }

    @JsonProperty("Power_Phase_C")
    public void setPowerPhaseC(Double powerPhaseC) {
        this.powerPhaseC = powerPhaseC;
    }

    @JsonProperty("Voltage_Phase_A")
    public Long getVoltagePhaseA() {
        return voltagePhaseA;
    }

    @JsonProperty("Voltage_Phase_A")
    public void setVoltagePhaseA(Long voltagePhaseA) {
        this.voltagePhaseA = voltagePhaseA;
    }

    @JsonProperty("Voltage_Phase_B")
    public Double getVoltagePhaseB() {
        return voltagePhaseB;
    }

    @JsonProperty("Voltage_Phase_B")
    public void setVoltagePhaseB(Double voltagePhaseB) {
        this.voltagePhaseB = voltagePhaseB;
    }

    @JsonProperty("Voltage_Phase_C")
    public Double getVoltagePhaseC() {
        return voltagePhaseC;
    }

    @JsonProperty("Voltage_Phase_C")
    public void setVoltagePhaseC(Double voltagePhaseC) {
        this.voltagePhaseC = voltagePhaseC;
    }

    @JsonAnyGetter
    public Map<String, Object> getAdditionalProperties() {
        return this.additionalProperties;
    }

    @JsonAnySetter
    public void setAdditionalProperty(String name, Object value) {
        this.additionalProperties.put(name, value);
    }

    @Override
    public String toString() {
        return new ToStringBuilder(this).append("alarmPhaseA", alarmPhaseA).append("alarmPhaseB", alarmPhaseB).append("alarmPhaseC", alarmPhaseC).append("currentPhaseA", currentPhaseA).append("currentPhaseB", currentPhaseB).append("currentPhaseC", currentPhaseC).append("energyPhaseA", energyPhaseA).append("energyPhaseB", energyPhaseB).append("energyPhaseC", energyPhaseC).append("frequencyPhaseA", frequencyPhaseA).append("frequencyPhaseB", frequencyPhaseB).append("frequencyPhaseC", frequencyPhaseC).append("powerFactorPhaseA", powerFactorPhaseA).append("powerFactorPhaseB", powerFactorPhaseB).append("powerFactorPhaseC", powerFactorPhaseC).append("powerPhaseA", powerPhaseA).append("powerPhaseB", powerPhaseB).append("powerPhaseC", powerPhaseC).append("voltagePhaseA", voltagePhaseA).append("voltagePhaseB", voltagePhaseB).append("voltagePhaseC", voltagePhaseC).append("additionalProperties", additionalProperties).toString();
    }

    @Override
    public int hashCode() {
        return new HashCodeBuilder().append(frequencyPhaseC).append(currentPhaseC).append(frequencyPhaseA).append(currentPhaseB).append(frequencyPhaseB).append(energyPhaseA).append(energyPhaseB).append(alarmPhaseC).append(voltagePhaseB).append(alarmPhaseB).append(voltagePhaseA).append(powerPhaseB).append(powerPhaseC).append(voltagePhaseC).append(energyPhaseC).append(powerPhaseA).append(currentPhaseA).append(powerFactorPhaseA).append(powerFactorPhaseB).append(additionalProperties).append(powerFactorPhaseC).append(alarmPhaseA).toHashCode();
    }

    @Override
    public boolean equals(Object other) {
        if (other == this) {
            return true;
        }
        if ((other instanceof PayloadFields) == false) {
            return false;
        }
        PayloadFields rhs = ((PayloadFields) other);
        return new EqualsBuilder().append(frequencyPhaseC, rhs.frequencyPhaseC).append(currentPhaseC, rhs.currentPhaseC).append(frequencyPhaseA, rhs.frequencyPhaseA).append(currentPhaseB, rhs.currentPhaseB).append(frequencyPhaseB, rhs.frequencyPhaseB).append(energyPhaseA, rhs.energyPhaseA).append(energyPhaseB, rhs.energyPhaseB).append(alarmPhaseC, rhs.alarmPhaseC).append(voltagePhaseB, rhs.voltagePhaseB).append(alarmPhaseB, rhs.alarmPhaseB).append(voltagePhaseA, rhs.voltagePhaseA).append(powerPhaseB, rhs.powerPhaseB).append(powerPhaseC, rhs.powerPhaseC).append(voltagePhaseC, rhs.voltagePhaseC).append(energyPhaseC, rhs.energyPhaseC).append(powerPhaseA, rhs.powerPhaseA).append(currentPhaseA, rhs.currentPhaseA).append(powerFactorPhaseA, rhs.powerFactorPhaseA).append(powerFactorPhaseB, rhs.powerFactorPhaseB).append(additionalProperties, rhs.additionalProperties).append(powerFactorPhaseC, rhs.powerFactorPhaseC).append(alarmPhaseA, rhs.alarmPhaseA).isEquals();
    }

}
