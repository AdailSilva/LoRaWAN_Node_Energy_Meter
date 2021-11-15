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
    "latitude",
    "longitude",
    "altitude",
    "source",
    "accuracy"
})
public class Location {

    @JsonProperty("latitude")
    private Double latitude;
    @JsonProperty("longitude")
    private Double longitude;
    @JsonProperty("altitude")
    private Long altitude;
    @JsonProperty("source")
    private String source;
    @JsonProperty("accuracy")
    private Long accuracy;
    @JsonIgnore
    private Map<String, Object> additionalProperties = new HashMap<String, Object>();

    /**
     * No args constructor for use in serialization
     * 
     */
    public Location() {
    }

    /**
     * 
     * @param altitude
     * @param latitude
     * @param accuracy
     * @param source
     * @param longitude
     */
    public Location(Double latitude, Double longitude, Long altitude, String source, Long accuracy) {
        super();
        this.latitude = latitude;
        this.longitude = longitude;
        this.altitude = altitude;
        this.source = source;
        this.accuracy = accuracy;
    }

    @JsonProperty("latitude")
    public Double getLatitude() {
        return latitude;
    }

    @JsonProperty("latitude")
    public void setLatitude(Double latitude) {
        this.latitude = latitude;
    }

    @JsonProperty("longitude")
    public Double getLongitude() {
        return longitude;
    }

    @JsonProperty("longitude")
    public void setLongitude(Double longitude) {
        this.longitude = longitude;
    }

    @JsonProperty("altitude")
    public Long getAltitude() {
        return altitude;
    }

    @JsonProperty("altitude")
    public void setAltitude(Long altitude) {
        this.altitude = altitude;
    }

    @JsonProperty("source")
    public String getSource() {
        return source;
    }

    @JsonProperty("source")
    public void setSource(String source) {
        this.source = source;
    }

    @JsonProperty("accuracy")
    public Long getAccuracy() {
        return accuracy;
    }

    @JsonProperty("accuracy")
    public void setAccuracy(Long accuracy) {
        this.accuracy = accuracy;
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
        return new ToStringBuilder(this).append("latitude", latitude).append("longitude", longitude).append("altitude", altitude).append("source", source).append("accuracy", accuracy).append("additionalProperties", additionalProperties).toString();
    }

    @Override
    public int hashCode() {
        return new HashCodeBuilder().append(altitude).append(latitude).append(accuracy).append(source).append(additionalProperties).append(longitude).toHashCode();
    }

    @Override
    public boolean equals(Object other) {
        if (other == this) {
            return true;
        }
        if ((other instanceof Location) == false) {
            return false;
        }
        Location rhs = ((Location) other);
        return new EqualsBuilder().append(altitude, rhs.altitude).append(latitude, rhs.latitude).append(accuracy, rhs.accuracy).append(source, rhs.source).append(additionalProperties, rhs.additionalProperties).append(longitude, rhs.longitude).isEquals();
    }

}
