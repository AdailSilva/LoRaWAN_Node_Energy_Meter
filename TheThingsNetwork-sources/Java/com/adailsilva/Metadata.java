package com.adailsilva;

import java.util.HashMap;
import java.util.List;
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
    "time",
    "frequency",
    "modulation",
    "data_rate",
    "coding_rate",
    "gateways"
})
public class Metadata {

    @JsonProperty("time")
    private String time;
    @JsonProperty("frequency")
    private Double frequency;
    @JsonProperty("modulation")
    private String modulation;
    @JsonProperty("data_rate")
    private String dataRate;
    @JsonProperty("coding_rate")
    private String codingRate;
    @JsonProperty("gateways")
    private List<Gateway> gateways = null;
    @JsonIgnore
    private Map<String, Object> additionalProperties = new HashMap<String, Object>();

    /**
     * No args constructor for use in serialization
     * 
     */
    public Metadata() {
    }

    /**
     * 
     * @param gateways
     * @param modulation
     * @param codingRate
     * @param time
     * @param dataRate
     * @param frequency
     */
    public Metadata(String time, Double frequency, String modulation, String dataRate, String codingRate, List<Gateway> gateways) {
        super();
        this.time = time;
        this.frequency = frequency;
        this.modulation = modulation;
        this.dataRate = dataRate;
        this.codingRate = codingRate;
        this.gateways = gateways;
    }

    @JsonProperty("time")
    public String getTime() {
        return time;
    }

    @JsonProperty("time")
    public void setTime(String time) {
        this.time = time;
    }

    @JsonProperty("frequency")
    public Double getFrequency() {
        return frequency;
    }

    @JsonProperty("frequency")
    public void setFrequency(Double frequency) {
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

    @JsonProperty("data_rate")
    public String getDataRate() {
        return dataRate;
    }

    @JsonProperty("data_rate")
    public void setDataRate(String dataRate) {
        this.dataRate = dataRate;
    }

    @JsonProperty("coding_rate")
    public String getCodingRate() {
        return codingRate;
    }

    @JsonProperty("coding_rate")
    public void setCodingRate(String codingRate) {
        this.codingRate = codingRate;
    }

    @JsonProperty("gateways")
    public List<Gateway> getGateways() {
        return gateways;
    }

    @JsonProperty("gateways")
    public void setGateways(List<Gateway> gateways) {
        this.gateways = gateways;
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
        return new ToStringBuilder(this).append("time", time).append("frequency", frequency).append("modulation", modulation).append("dataRate", dataRate).append("codingRate", codingRate).append("gateways", gateways).append("additionalProperties", additionalProperties).toString();
    }

    @Override
    public int hashCode() {
        return new HashCodeBuilder().append(gateways).append(modulation).append(codingRate).append(time).append(dataRate).append(additionalProperties).append(frequency).toHashCode();
    }

    @Override
    public boolean equals(Object other) {
        if (other == this) {
            return true;
        }
        if ((other instanceof Metadata) == false) {
            return false;
        }
        Metadata rhs = ((Metadata) other);
        return new EqualsBuilder().append(gateways, rhs.gateways).append(modulation, rhs.modulation).append(codingRate, rhs.codingRate).append(time, rhs.time).append(dataRate, rhs.dataRate).append(additionalProperties, rhs.additionalProperties).append(frequency, rhs.frequency).isEquals();
    }

}
