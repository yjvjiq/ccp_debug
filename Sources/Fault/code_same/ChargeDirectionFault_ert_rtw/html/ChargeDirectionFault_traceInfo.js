function RTW_Sid2UrlHash() {
	this.urlHashMap = new Array();
	/* <Root>/cur */
	this.urlHashMap["ChargeDirectionFault:1"] = "ert_main.c:37&ChargeDirectionFault.c:46";
	/* <Root>/Vmin */
	this.urlHashMap["ChargeDirectionFault:5"] = "ert_main.c:40&ChargeDirectionFault.c:45";
	/* <Root>/Chart */
	this.urlHashMap["ChargeDirectionFault:3"] = "ChargeDirectionFault.c:19,44,107,130&ChargeDirectionFault.h:38,43,44,45";
	/* <Root>/F_lev */
	this.urlHashMap["ChargeDirectionFault:2"] = "ert_main.c:43&ChargeDirectionFault.c:109";
	/* <S1>:103 */
	this.urlHashMap["ChargeDirectionFault:3:103"] = "ChargeDirectionFault.c:56,61";
	/* <S1>:185 */
	this.urlHashMap["ChargeDirectionFault:3:185"] = "ChargeDirectionFault.c:57,62";
	/* <S1>:181 */
	this.urlHashMap["ChargeDirectionFault:3:181"] = "ChargeDirectionFault.c:65,95";
	/* <S1>:183 */
	this.urlHashMap["ChargeDirectionFault:3:183"] = "ChargeDirectionFault.c:73,86";
	/* <S1>:182 */
	this.urlHashMap["ChargeDirectionFault:3:182"] = "ChargeDirectionFault.c:90";
	/* <S1>:104 */
	this.urlHashMap["ChargeDirectionFault:3:104"] = "ChargeDirectionFault.c:55";
	/* <S1>:186 */
	this.urlHashMap["ChargeDirectionFault:3:186"] = "ChargeDirectionFault.c:92";
	/* <S1>:187 */
	this.urlHashMap["ChargeDirectionFault:3:187"] = "ChargeDirectionFault.c:70";
	/* <S1>:184 */
	this.urlHashMap["ChargeDirectionFault:3:184"] = "ChargeDirectionFault.c:58";
	/* <S1>:188 */
	this.urlHashMap["ChargeDirectionFault:3:188"] = "ChargeDirectionFault.c:67";
	this.getUrlHash = function(sid) { return this.urlHashMap[sid];}
}
RTW_Sid2UrlHash.instance = new RTW_Sid2UrlHash();
function RTW_rtwnameSIDMap() {
	this.rtwnameHashMap = new Array();
	this.sidHashMap = new Array();
	this.rtwnameHashMap["<Root>"] = {sid: "ChargeDirectionFault"};
	this.sidHashMap["ChargeDirectionFault"] = {rtwname: "<Root>"};
	this.rtwnameHashMap["<S1>"] = {sid: "ChargeDirectionFault:3"};
	this.sidHashMap["ChargeDirectionFault:3"] = {rtwname: "<S1>"};
	this.rtwnameHashMap["<Root>/cur"] = {sid: "ChargeDirectionFault:1"};
	this.sidHashMap["ChargeDirectionFault:1"] = {rtwname: "<Root>/cur"};
	this.rtwnameHashMap["<Root>/Vmin"] = {sid: "ChargeDirectionFault:5"};
	this.sidHashMap["ChargeDirectionFault:5"] = {rtwname: "<Root>/Vmin"};
	this.rtwnameHashMap["<Root>/Chart"] = {sid: "ChargeDirectionFault:3"};
	this.sidHashMap["ChargeDirectionFault:3"] = {rtwname: "<Root>/Chart"};
	this.rtwnameHashMap["<Root>/F_lev"] = {sid: "ChargeDirectionFault:2"};
	this.sidHashMap["ChargeDirectionFault:2"] = {rtwname: "<Root>/F_lev"};
	this.rtwnameHashMap["<S1>:103"] = {sid: "ChargeDirectionFault:3:103"};
	this.sidHashMap["ChargeDirectionFault:3:103"] = {rtwname: "<S1>:103"};
	this.rtwnameHashMap["<S1>:185"] = {sid: "ChargeDirectionFault:3:185"};
	this.sidHashMap["ChargeDirectionFault:3:185"] = {rtwname: "<S1>:185"};
	this.rtwnameHashMap["<S1>:181"] = {sid: "ChargeDirectionFault:3:181"};
	this.sidHashMap["ChargeDirectionFault:3:181"] = {rtwname: "<S1>:181"};
	this.rtwnameHashMap["<S1>:183"] = {sid: "ChargeDirectionFault:3:183"};
	this.sidHashMap["ChargeDirectionFault:3:183"] = {rtwname: "<S1>:183"};
	this.rtwnameHashMap["<S1>:182"] = {sid: "ChargeDirectionFault:3:182"};
	this.sidHashMap["ChargeDirectionFault:3:182"] = {rtwname: "<S1>:182"};
	this.rtwnameHashMap["<S1>:104"] = {sid: "ChargeDirectionFault:3:104"};
	this.sidHashMap["ChargeDirectionFault:3:104"] = {rtwname: "<S1>:104"};
	this.rtwnameHashMap["<S1>:186"] = {sid: "ChargeDirectionFault:3:186"};
	this.sidHashMap["ChargeDirectionFault:3:186"] = {rtwname: "<S1>:186"};
	this.rtwnameHashMap["<S1>:187"] = {sid: "ChargeDirectionFault:3:187"};
	this.sidHashMap["ChargeDirectionFault:3:187"] = {rtwname: "<S1>:187"};
	this.rtwnameHashMap["<S1>:184"] = {sid: "ChargeDirectionFault:3:184"};
	this.sidHashMap["ChargeDirectionFault:3:184"] = {rtwname: "<S1>:184"};
	this.rtwnameHashMap["<S1>:188"] = {sid: "ChargeDirectionFault:3:188"};
	this.sidHashMap["ChargeDirectionFault:3:188"] = {rtwname: "<S1>:188"};
	this.getSID = function(rtwname) { return this.rtwnameHashMap[rtwname];}
	this.getRtwname = function(sid) { return this.sidHashMap[sid];}
}
RTW_rtwnameSIDMap.instance = new RTW_rtwnameSIDMap();
