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
    "app_id",
    "dev_id",
    "hardware_serial",
    "port",
    "counter",
    "payload_raw",
    "payload_fields",
    "metadata",
    "downlink_url"
})
public class TheThingsNetwork {

    @JsonProperty("app_id")
    private String appId;
    @JsonProperty("dev_id")
    private String devId;
    @JsonProperty("hardware_serial")
    private String hardwareSerial;
    @JsonProperty("port")
    private Long port;
    @JsonProperty("counter")
    private Long counter;
    @JsonProperty("payload_raw")
    private String payloadRaw;
    @JsonProperty("payload_fields")
    private PayloadFields payloadFields;
    @JsonProperty("metadata")
    private Metadata metadata;
    @JsonProperty("downlink_url")
    private String downlinkUrl;
    @JsonIgnore
    private Map<String, Object> additionalProperties = new HashMap<String, Object>();

    /**
     * No args constructor for use in serialization
     * 
     */
    public TheThingsNetwork() {
    }

    /**
     * 
     * @param devId
     * @param metadata
     * @param payloadRaw
     * @param port
     * @param appId
     * @param hardwareSerial
     * @param payloadFields
     * @param counter
     * @param downlinkUrl
     */
    public TheThingsNetwork(String appId, String devId, String hardwareSerial, Long port, Long counter, String payloadRaw, PayloadFields payloadFields, Metadata metadata, String downlinkUrl) {
        super();
        this.appId = appId;
        this.devId = devId;
        this.hardwareSerial = hardwareSerial;
        this.port = port;
        this.counter = counter;
        this.payloadRaw = payloadRaw;
        this.payloadFields = payloadFields;
        this.metadata = metadata;
        this.downlinkUrl = downlinkUrl;
    }

    @JsonProperty("app_id")
    public String getAppId() {
        return appId;
    }

    @JsonProperty("app_id")
    public void setAppId(String appId) {
        this.appId = appId;
    }

    @JsonProperty("dev_id")
    public String getDevId() {
        return devId;
    }

    @JsonProperty("dev_id")
    public void setDevId(String devId) {
        this.devId = devId;
    }

    @JsonProperty("hardware_serial")
    public String getHardwareSerial() {
        return hardwareSerial;
    }

    @JsonProperty("hardware_serial")
    public void setHardwareSerial(String hardwareSerial) {
        this.hardwareSerial = hardwareSerial;
    }

    @JsonProperty("port")
    public Long getPort() {
        return port;
    }

    @JsonProperty("port")
    public void setPort(Long port) {
        this.port = port;
    }

    @JsonProperty("counter")
    public Long getCounter() {
        return counter;
    }

    @JsonProperty("counter")
    public void setCounter(Long counter) {
        this.counter = counter;
    }

    @JsonProperty("payload_raw")
    public String getPayloadRaw() {
        return payloadRaw;
    }

    @JsonProperty("payload_raw")
    public void setPayloadRaw(String payloadRaw) {
        this.payloadRaw = payloadRaw;
    }

    @JsonProperty("payload_fields")
    public PayloadFields getPayloadFields() {
        return payloadFields;
    }

    @JsonProperty("payload_fields")
    public void setPayloadFields(PayloadFields payloadFields) {
        this.payloadFields = payloadFields;
    }

    @JsonProperty("metadata")
    public Metadata getMetadata() {
        return metadata;
    }

    @JsonProperty("metadata")
    public void setMetadata(Metadata metadata) {
        this.metadata = metadata;
    }

    @JsonProperty("downlink_url")
    public String getDownlinkUrl() {
        return downlinkUrl;
    }

    @JsonProperty("downlink_url")
    public void setDownlinkUrl(String downlinkUrl) {
        this.downlinkUrl = downlinkUrl;
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
        return new ToStringBuilder(this).append("appId", appId).append("devId", devId).append("hardwareSerial", hardwareSerial).append("port", port).append("counter", counter).append("payloadRaw", payloadRaw).append("payloadFields", payloadFields).append("metadata", metadata).append("downlinkUrl", downlinkUrl).append("additionalProperties", additionalProperties).toString();
    }

    @Override
    public int hashCode() {
        return new HashCodeBuilder().append(devId).append(metadata).append(payloadRaw).append(port).append(appId).append(hardwareSerial).append(payloadFields).append(counter).append(additionalProperties).append(downlinkUrl).toHashCode();
    }

    @Override
    public boolean equals(Object other) {
        if (other == this) {
            return true;
        }
        if ((other instanceof TheThingsNetwork) == false) {
            return false;
        }
        TheThingsNetwork rhs = ((TheThingsNetwork) other);
        return new EqualsBuilder().append(devId, rhs.devId).append(metadata, rhs.metadata).append(payloadRaw, rhs.payloadRaw).append(port, rhs.port).append(appId, rhs.appId).append(hardwareSerial, rhs.hardwareSerial).append(payloadFields, rhs.payloadFields).append(counter, rhs.counter).append(additionalProperties, rhs.additionalProperties).append(downlinkUrl, rhs.downlinkUrl).isEquals();
    }

}
