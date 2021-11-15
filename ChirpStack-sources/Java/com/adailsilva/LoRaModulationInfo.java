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
    "bandwidth",
    "spreadingFactor",
    "codeRate",
    "polarizationInversion"
})
public class LoRaModulationInfo {

    @JsonProperty("bandwidth")
    private Long bandwidth;
    @JsonProperty("spreadingFactor")
    private Long spreadingFactor;
    @JsonProperty("codeRate")
    private String codeRate;
    @JsonProperty("polarizationInversion")
    private Boolean polarizationInversion;
    @JsonIgnore
    private Map<String, Object> additionalProperties = new HashMap<String, Object>();

    /**
     * No args constructor for use in serialization
     * 
     */
    public LoRaModulationInfo() {
    }

    /**
     * 
     * @param spreadingFactor
     * @param bandwidth
     * @param polarizationInversion
     * @param codeRate
     */
    public LoRaModulationInfo(Long bandwidth, Long spreadingFactor, String codeRate, Boolean polarizationInversion) {
        super();
        this.bandwidth = bandwidth;
        this.spreadingFactor = spreadingFactor;
        this.codeRate = codeRate;
        this.polarizationInversion = polarizationInversion;
    }

    @JsonProperty("bandwidth")
    public Long getBandwidth() {
        return bandwidth;
    }

    @JsonProperty("bandwidth")
    public void setBandwidth(Long bandwidth) {
        this.bandwidth = bandwidth;
    }

    @JsonProperty("spreadingFactor")
    public Long getSpreadingFactor() {
        return spreadingFactor;
    }

    @JsonProperty("spreadingFactor")
    public void setSpreadingFactor(Long spreadingFactor) {
        this.spreadingFactor = spreadingFactor;
    }

    @JsonProperty("codeRate")
    public String getCodeRate() {
        return codeRate;
    }

    @JsonProperty("codeRate")
    public void setCodeRate(String codeRate) {
        this.codeRate = codeRate;
    }

    @JsonProperty("polarizationInversion")
    public Boolean getPolarizationInversion() {
        return polarizationInversion;
    }

    @JsonProperty("polarizationInversion")
    public void setPolarizationInversion(Boolean polarizationInversion) {
        this.polarizationInversion = polarizationInversion;
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
        return new ToStringBuilder(this).append("bandwidth", bandwidth).append("spreadingFactor", spreadingFactor).append("codeRate", codeRate).append("polarizationInversion", polarizationInversion).append("additionalProperties", additionalProperties).toString();
    }

    @Override
    public int hashCode() {
        return new HashCodeBuilder().append(spreadingFactor).append(additionalProperties).append(bandwidth).append(polarizationInversion).append(codeRate).toHashCode();
    }

    @Override
    public boolean equals(Object other) {
        if (other == this) {
            return true;
        }
        if ((other instanceof LoRaModulationInfo) == false) {
            return false;
        }
        LoRaModulationInfo rhs = ((LoRaModulationInfo) other);
        return new EqualsBuilder().append(spreadingFactor, rhs.spreadingFactor).append(additionalProperties, rhs.additionalProperties).append(bandwidth, rhs.bandwidth).append(polarizationInversion, rhs.polarizationInversion).append(codeRate, rhs.codeRate).isEquals();
    }

}
