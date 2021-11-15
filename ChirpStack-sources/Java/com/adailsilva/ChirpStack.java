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
    "applicationID",
    "applicationName",
    "deviceName",
    "devEUI",
    "rxInfo",
    "txInfo",
    "adr",
    "dr",
    "fCnt",
    "fPort",
    "data",
    "objectJSON",
    "tags",
    "confirmedUplink",
    "devAddr"
})
public class ChirpStack {

    @JsonProperty("applicationID")
    private String applicationID;
    @JsonProperty("applicationName")
    private String applicationName;
    @JsonProperty("deviceName")
    private String deviceName;
    @JsonProperty("devEUI")
    private String devEUI;
    @JsonProperty("rxInfo")
    private List<RxInfo> rxInfo = null;
    @JsonProperty("txInfo")
    private TxInfo txInfo;
    @JsonProperty("adr")
    private Boolean adr;
    @JsonProperty("dr")
    private Long dr;
    @JsonProperty("fCnt")
    private Long fCnt;
    @JsonProperty("fPort")
    private Long fPort;
    @JsonProperty("data")
    private String data;
    @JsonProperty("objectJSON")
    private String objectJSON;
    @JsonProperty("tags")
    private Tags tags;
    @JsonProperty("confirmedUplink")
    private Boolean confirmedUplink;
    @JsonProperty("devAddr")
    private String devAddr;
    @JsonIgnore
    private Map<String, Object> additionalProperties = new HashMap<String, Object>();

    /**
     * No args constructor for use in serialization
     * 
     */
    public ChirpStack() {
    }

    /**
     * 
     * @param devAddr
     * @param txInfo
     * @param fPort
     * @param data
     * @param fCnt
     * @param deviceName
     * @param devEUI
     * @param adr
     * @param dr
     * @param tags
     * @param rxInfo
     * @param objectJSON
     * @param confirmedUplink
     * @param applicationID
     * @param applicationName
     */
    public ChirpStack(String applicationID, String applicationName, String deviceName, String devEUI, List<RxInfo> rxInfo, TxInfo txInfo, Boolean adr, Long dr, Long fCnt, Long fPort, String data, String objectJSON, Tags tags, Boolean confirmedUplink, String devAddr) {
        super();
        this.applicationID = applicationID;
        this.applicationName = applicationName;
        this.deviceName = deviceName;
        this.devEUI = devEUI;
        this.rxInfo = rxInfo;
        this.txInfo = txInfo;
        this.adr = adr;
        this.dr = dr;
        this.fCnt = fCnt;
        this.fPort = fPort;
        this.data = data;
        this.objectJSON = objectJSON;
        this.tags = tags;
        this.confirmedUplink = confirmedUplink;
        this.devAddr = devAddr;
    }

    @JsonProperty("applicationID")
    public String getApplicationID() {
        return applicationID;
    }

    @JsonProperty("applicationID")
    public void setApplicationID(String applicationID) {
        this.applicationID = applicationID;
    }

    @JsonProperty("applicationName")
    public String getApplicationName() {
        return applicationName;
    }

    @JsonProperty("applicationName")
    public void setApplicationName(String applicationName) {
        this.applicationName = applicationName;
    }

    @JsonProperty("deviceName")
    public String getDeviceName() {
        return deviceName;
    }

    @JsonProperty("deviceName")
    public void setDeviceName(String deviceName) {
        this.deviceName = deviceName;
    }

    @JsonProperty("devEUI")
    public String getDevEUI() {
        return devEUI;
    }

    @JsonProperty("devEUI")
    public void setDevEUI(String devEUI) {
        this.devEUI = devEUI;
    }

    @JsonProperty("rxInfo")
    public List<RxInfo> getRxInfo() {
        return rxInfo;
    }

    @JsonProperty("rxInfo")
    public void setRxInfo(List<RxInfo> rxInfo) {
        this.rxInfo = rxInfo;
    }

    @JsonProperty("txInfo")
    public TxInfo getTxInfo() {
        return txInfo;
    }

    @JsonProperty("txInfo")
    public void setTxInfo(TxInfo txInfo) {
        this.txInfo = txInfo;
    }

    @JsonProperty("adr")
    public Boolean getAdr() {
        return adr;
    }

    @JsonProperty("adr")
    public void setAdr(Boolean adr) {
        this.adr = adr;
    }

    @JsonProperty("dr")
    public Long getDr() {
        return dr;
    }

    @JsonProperty("dr")
    public void setDr(Long dr) {
        this.dr = dr;
    }

    @JsonProperty("fCnt")
    public Long getFCnt() {
        return fCnt;
    }

    @JsonProperty("fCnt")
    public void setFCnt(Long fCnt) {
        this.fCnt = fCnt;
    }

    @JsonProperty("fPort")
    public Long getFPort() {
        return fPort;
    }

    @JsonProperty("fPort")
    public void setFPort(Long fPort) {
        this.fPort = fPort;
    }

    @JsonProperty("data")
    public String getData() {
        return data;
    }

    @JsonProperty("data")
    public void setData(String data) {
        this.data = data;
    }

    @JsonProperty("objectJSON")
    public String getObjectJSON() {
        return objectJSON;
    }

    @JsonProperty("objectJSON")
    public void setObjectJSON(String objectJSON) {
        this.objectJSON = objectJSON;
    }

    @JsonProperty("tags")
    public Tags getTags() {
        return tags;
    }

    @JsonProperty("tags")
    public void setTags(Tags tags) {
        this.tags = tags;
    }

    @JsonProperty("confirmedUplink")
    public Boolean getConfirmedUplink() {
        return confirmedUplink;
    }

    @JsonProperty("confirmedUplink")
    public void setConfirmedUplink(Boolean confirmedUplink) {
        this.confirmedUplink = confirmedUplink;
    }

    @JsonProperty("devAddr")
    public String getDevAddr() {
        return devAddr;
    }

    @JsonProperty("devAddr")
    public void setDevAddr(String devAddr) {
        this.devAddr = devAddr;
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
        return new ToStringBuilder(this).append("applicationID", applicationID).append("applicationName", applicationName).append("deviceName", deviceName).append("devEUI", devEUI).append("rxInfo", rxInfo).append("txInfo", txInfo).append("adr", adr).append("dr", dr).append("fCnt", fCnt).append("fPort", fPort).append("data", data).append("objectJSON", objectJSON).append("tags", tags).append("confirmedUplink", confirmedUplink).append("devAddr", devAddr).append("additionalProperties", additionalProperties).toString();
    }

    @Override
    public int hashCode() {
        return new HashCodeBuilder().append(devAddr).append(txInfo).append(fPort).append(data).append(fCnt).append(deviceName).append(devEUI).append(adr).append(dr).append(tags).append(rxInfo).append(objectJSON).append(confirmedUplink).append(additionalProperties).append(applicationID).append(applicationName).toHashCode();
    }

    @Override
    public boolean equals(Object other) {
        if (other == this) {
            return true;
        }
        if ((other instanceof ChirpStack) == false) {
            return false;
        }
        ChirpStack rhs = ((ChirpStack) other);
        return new EqualsBuilder().append(devAddr, rhs.devAddr).append(txInfo, rhs.txInfo).append(fPort, rhs.fPort).append(data, rhs.data).append(fCnt, rhs.fCnt).append(deviceName, rhs.deviceName).append(devEUI, rhs.devEUI).append(adr, rhs.adr).append(dr, rhs.dr).append(tags, rhs.tags).append(rxInfo, rhs.rxInfo).append(objectJSON, rhs.objectJSON).append(confirmedUplink, rhs.confirmedUplink).append(additionalProperties, rhs.additionalProperties).append(applicationID, rhs.applicationID).append(applicationName, rhs.applicationName).isEquals();
    }

}
