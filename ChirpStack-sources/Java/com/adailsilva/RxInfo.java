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
    "gatewayID",
    "time",
    "timeSinceGPSEpoch",
    "rssi",
    "loRaSNR",
    "channel",
    "rfChain",
    "board",
    "antenna",
    "location",
    "fineTimestampType",
    "context",
    "uplinkID",
    "crcStatus"
})
public class RxInfo {

    @JsonProperty("gatewayID")
    private String gatewayID;
    @JsonProperty("time")
    private String time;
    @JsonProperty("timeSinceGPSEpoch")
    private Object timeSinceGPSEpoch;
    @JsonProperty("rssi")
    private Long rssi;
    @JsonProperty("loRaSNR")
    private Double loRaSNR;
    @JsonProperty("channel")
    private Long channel;
    @JsonProperty("rfChain")
    private Long rfChain;
    @JsonProperty("board")
    private Long board;
    @JsonProperty("antenna")
    private Long antenna;
    @JsonProperty("location")
    private Location location;
    @JsonProperty("fineTimestampType")
    private String fineTimestampType;
    @JsonProperty("context")
    private String context;
    @JsonProperty("uplinkID")
    private String uplinkID;
    @JsonProperty("crcStatus")
    private String crcStatus;
    @JsonIgnore
    private Map<String, Object> additionalProperties = new HashMap<String, Object>();

    /**
     * No args constructor for use in serialization
     * 
     */
    public RxInfo() {
    }

    /**
     * 
     * @param antenna
     * @param rssi
     * @param fineTimestampType
     * @param channel
     * @param timeSinceGPSEpoch
     * @param rfChain
     * @param context
     * @param location
     * @param uplinkID
     * @param time
     * @param gatewayID
     * @param loRaSNR
     * @param board
     * @param crcStatus
     */
    public RxInfo(String gatewayID, String time, Object timeSinceGPSEpoch, Long rssi, Double loRaSNR, Long channel, Long rfChain, Long board, Long antenna, Location location, String fineTimestampType, String context, String uplinkID, String crcStatus) {
        super();
        this.gatewayID = gatewayID;
        this.time = time;
        this.timeSinceGPSEpoch = timeSinceGPSEpoch;
        this.rssi = rssi;
        this.loRaSNR = loRaSNR;
        this.channel = channel;
        this.rfChain = rfChain;
        this.board = board;
        this.antenna = antenna;
        this.location = location;
        this.fineTimestampType = fineTimestampType;
        this.context = context;
        this.uplinkID = uplinkID;
        this.crcStatus = crcStatus;
    }

    @JsonProperty("gatewayID")
    public String getGatewayID() {
        return gatewayID;
    }

    @JsonProperty("gatewayID")
    public void setGatewayID(String gatewayID) {
        this.gatewayID = gatewayID;
    }

    @JsonProperty("time")
    public String getTime() {
        return time;
    }

    @JsonProperty("time")
    public void setTime(String time) {
        this.time = time;
    }

    @JsonProperty("timeSinceGPSEpoch")
    public Object getTimeSinceGPSEpoch() {
        return timeSinceGPSEpoch;
    }

    @JsonProperty("timeSinceGPSEpoch")
    public void setTimeSinceGPSEpoch(Object timeSinceGPSEpoch) {
        this.timeSinceGPSEpoch = timeSinceGPSEpoch;
    }

    @JsonProperty("rssi")
    public Long getRssi() {
        return rssi;
    }

    @JsonProperty("rssi")
    public void setRssi(Long rssi) {
        this.rssi = rssi;
    }

    @JsonProperty("loRaSNR")
    public Double getLoRaSNR() {
        return loRaSNR;
    }

    @JsonProperty("loRaSNR")
    public void setLoRaSNR(Double loRaSNR) {
        this.loRaSNR = loRaSNR;
    }

    @JsonProperty("channel")
    public Long getChannel() {
        return channel;
    }

    @JsonProperty("channel")
    public void setChannel(Long channel) {
        this.channel = channel;
    }

    @JsonProperty("rfChain")
    public Long getRfChain() {
        return rfChain;
    }

    @JsonProperty("rfChain")
    public void setRfChain(Long rfChain) {
        this.rfChain = rfChain;
    }

    @JsonProperty("board")
    public Long getBoard() {
        return board;
    }

    @JsonProperty("board")
    public void setBoard(Long board) {
        this.board = board;
    }

    @JsonProperty("antenna")
    public Long getAntenna() {
        return antenna;
    }

    @JsonProperty("antenna")
    public void setAntenna(Long antenna) {
        this.antenna = antenna;
    }

    @JsonProperty("location")
    public Location getLocation() {
        return location;
    }

    @JsonProperty("location")
    public void setLocation(Location location) {
        this.location = location;
    }

    @JsonProperty("fineTimestampType")
    public String getFineTimestampType() {
        return fineTimestampType;
    }

    @JsonProperty("fineTimestampType")
    public void setFineTimestampType(String fineTimestampType) {
        this.fineTimestampType = fineTimestampType;
    }

    @JsonProperty("context")
    public String getContext() {
        return context;
    }

    @JsonProperty("context")
    public void setContext(String context) {
        this.context = context;
    }

    @JsonProperty("uplinkID")
    public String getUplinkID() {
        return uplinkID;
    }

    @JsonProperty("uplinkID")
    public void setUplinkID(String uplinkID) {
        this.uplinkID = uplinkID;
    }

    @JsonProperty("crcStatus")
    public String getCrcStatus() {
        return crcStatus;
    }

    @JsonProperty("crcStatus")
    public void setCrcStatus(String crcStatus) {
        this.crcStatus = crcStatus;
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
        return new ToStringBuilder(this).append("gatewayID", gatewayID).append("time", time).append("timeSinceGPSEpoch", timeSinceGPSEpoch).append("rssi", rssi).append("loRaSNR", loRaSNR).append("channel", channel).append("rfChain", rfChain).append("board", board).append("antenna", antenna).append("location", location).append("fineTimestampType", fineTimestampType).append("context", context).append("uplinkID", uplinkID).append("crcStatus", crcStatus).append("additionalProperties", additionalProperties).toString();
    }

    @Override
    public int hashCode() {
        return new HashCodeBuilder().append(antenna).append(rssi).append(fineTimestampType).append(channel).append(timeSinceGPSEpoch).append(rfChain).append(context).append(location).append(uplinkID).append(time).append(additionalProperties).append(gatewayID).append(loRaSNR).append(board).append(crcStatus).toHashCode();
    }

    @Override
    public boolean equals(Object other) {
        if (other == this) {
            return true;
        }
        if ((other instanceof RxInfo) == false) {
            return false;
        }
        RxInfo rhs = ((RxInfo) other);
        return new EqualsBuilder().append(antenna, rhs.antenna).append(rssi, rhs.rssi).append(fineTimestampType, rhs.fineTimestampType).append(channel, rhs.channel).append(timeSinceGPSEpoch, rhs.timeSinceGPSEpoch).append(rfChain, rhs.rfChain).append(context, rhs.context).append(location, rhs.location).append(uplinkID, rhs.uplinkID).append(time, rhs.time).append(additionalProperties, rhs.additionalProperties).append(gatewayID, rhs.gatewayID).append(loRaSNR, rhs.loRaSNR).append(board, rhs.board).append(crcStatus, rhs.crcStatus).isEquals();
    }

}
