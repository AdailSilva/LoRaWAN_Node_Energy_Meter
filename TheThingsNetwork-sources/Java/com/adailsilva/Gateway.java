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
    "gtw_id",
    "timestamp",
    "time",
    "channel",
    "rssi",
    "snr",
    "rf_chain",
    "latitude",
    "longitude",
    "altitude"
})
public class Gateway {

    @JsonProperty("gtw_id")
    private String gtwId;
    @JsonProperty("timestamp")
    private Long timestamp;
    @JsonProperty("time")
    private String time;
    @JsonProperty("channel")
    private Long channel;
    @JsonProperty("rssi")
    private Long rssi;
    @JsonProperty("snr")
    private Long snr;
    @JsonProperty("rf_chain")
    private Long rfChain;
    @JsonProperty("latitude")
    private Double latitude;
    @JsonProperty("longitude")
    private Double longitude;
    @JsonProperty("altitude")
    private Long altitude;
    @JsonIgnore
    private Map<String, Object> additionalProperties = new HashMap<String, Object>();

    /**
     * No args constructor for use in serialization
     * 
     */
    public Gateway() {
    }

    /**
     * 
     * @param altitude
     * @param rssi
     * @param gtwId
     * @param snr
     * @param latitude
     * @param channel
     * @param rfChain
     * @param time
     * @param timestamp
     * @param longitude
     */
    public Gateway(String gtwId, Long timestamp, String time, Long channel, Long rssi, Long snr, Long rfChain, Double latitude, Double longitude, Long altitude) {
        super();
        this.gtwId = gtwId;
        this.timestamp = timestamp;
        this.time = time;
        this.channel = channel;
        this.rssi = rssi;
        this.snr = snr;
        this.rfChain = rfChain;
        this.latitude = latitude;
        this.longitude = longitude;
        this.altitude = altitude;
    }

    @JsonProperty("gtw_id")
    public String getGtwId() {
        return gtwId;
    }

    @JsonProperty("gtw_id")
    public void setGtwId(String gtwId) {
        this.gtwId = gtwId;
    }

    @JsonProperty("timestamp")
    public Long getTimestamp() {
        return timestamp;
    }

    @JsonProperty("timestamp")
    public void setTimestamp(Long timestamp) {
        this.timestamp = timestamp;
    }

    @JsonProperty("time")
    public String getTime() {
        return time;
    }

    @JsonProperty("time")
    public void setTime(String time) {
        this.time = time;
    }

    @JsonProperty("channel")
    public Long getChannel() {
        return channel;
    }

    @JsonProperty("channel")
    public void setChannel(Long channel) {
        this.channel = channel;
    }

    @JsonProperty("rssi")
    public Long getRssi() {
        return rssi;
    }

    @JsonProperty("rssi")
    public void setRssi(Long rssi) {
        this.rssi = rssi;
    }

    @JsonProperty("snr")
    public Long getSnr() {
        return snr;
    }

    @JsonProperty("snr")
    public void setSnr(Long snr) {
        this.snr = snr;
    }

    @JsonProperty("rf_chain")
    public Long getRfChain() {
        return rfChain;
    }

    @JsonProperty("rf_chain")
    public void setRfChain(Long rfChain) {
        this.rfChain = rfChain;
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
        return new ToStringBuilder(this).append("gtwId", gtwId).append("timestamp", timestamp).append("time", time).append("channel", channel).append("rssi", rssi).append("snr", snr).append("rfChain", rfChain).append("latitude", latitude).append("longitude", longitude).append("altitude", altitude).append("additionalProperties", additionalProperties).toString();
    }

    @Override
    public int hashCode() {
        return new HashCodeBuilder().append(altitude).append(rssi).append(gtwId).append(snr).append(latitude).append(channel).append(rfChain).append(time).append(additionalProperties).append(timestamp).append(longitude).toHashCode();
    }

    @Override
    public boolean equals(Object other) {
        if (other == this) {
            return true;
        }
        if ((other instanceof Gateway) == false) {
            return false;
        }
        Gateway rhs = ((Gateway) other);
        return new EqualsBuilder().append(altitude, rhs.altitude).append(rssi, rhs.rssi).append(gtwId, rhs.gtwId).append(snr, rhs.snr).append(latitude, rhs.latitude).append(channel, rhs.channel).append(rfChain, rhs.rfChain).append(time, rhs.time).append(additionalProperties, rhs.additionalProperties).append(timestamp, rhs.timestamp).append(longitude, rhs.longitude).isEquals();
    }

}
