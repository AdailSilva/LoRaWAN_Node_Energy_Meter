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
    "frequency",
    "modulation",
    "loRaModulationInfo"
})
public class TxInfo {

    @JsonProperty("frequency")
    private Long frequency;
    @JsonProperty("modulation")
    private String modulation;
    @JsonProperty("loRaModulationInfo")
    private LoRaModulationInfo loRaModulationInfo;
    @JsonIgnore
    private Map<String, Object> additionalProperties = new HashMap<String, Object>();

    /**
     * No args constructor for use in serialization
     * 
     */
    public TxInfo() {
    }

    /**
     * 
     * @param modulation
     * @param loRaModulationInfo
     * @param frequency
     */
    public TxInfo(Long frequency, String modulation, LoRaModulationInfo loRaModulationInfo) {
        super();
        this.frequency = frequency;
        this.modulation = modulation;
        this.loRaModulationInfo = loRaModulationInfo;
    }

    @JsonProperty("frequency")
    public Long getFrequency() {
        return frequency;
    }

    @JsonProperty("frequency")
    public void setFrequency(Long frequency) {
        this.frequency = frequency;
    }

    @JsonProperty("modulation")
    public String getModulation() {
        return modulation;
    }

    @JsonProperty("modulation")
    public void setModulation(String modulation) {
        this.modulation = modulation;
    }

    @JsonProperty("loRaModulationInfo")
    public LoRaModulationInfo getLoRaModulationInfo() {
        return loRaModulationInfo;
    }

    @JsonProperty("loRaModulationInfo")
    public void setLoRaModulationInfo(LoRaModulationInfo loRaModulationInfo) {
        this.loRaModulationInfo = loRaModulationInfo;
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
        return new ToStringBuilder(this).append("frequency", frequency).append("modulation", modulation).append("loRaModulationInfo", loRaModulationInfo).append("additionalProperties", additionalProperties).toString();
    }

    @Override
    public int hashCode() {
        return new HashCodeBuilder().append(additionalProperties).append(modulation).append(loRaModulationInfo).append(frequency).toHashCode();
    }

    @Override
    public boolean equals(Object other) {
        if (other == this) {
            return true;
        }
        if ((other instanceof TxInfo) == false) {
            return false;
        }
        TxInfo rhs = ((TxInfo) other);
        return new EqualsBuilder().append(additionalProperties, rhs.additionalProperties).append(modulation, rhs.modulation).append(loRaModulationInfo, rhs.loRaModulationInfo).append(frequency, rhs.frequency).isEquals();
    }

}
