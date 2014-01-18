/*
 * BSS table
 * Copyright (c) 2009-2010, Jouni Malinen <j@w1.fi>
 *
 * This software may be distributed under the terms of the BSD license.
 * See README for more details.
 */

#ifndef BSS_H
#define BSS_H

struct wpa_scan_res;

#define WPA_BSS_QUAL_INVALID		BIT(0)
#define WPA_BSS_NOISE_INVALID		BIT(1)
#define WPA_BSS_LEVEL_INVALID		BIT(2)
#define WPA_BSS_LEVEL_DBM		BIT(3)
#define WPA_BSS_AUTHENTICATED		BIT(4)
#define WPA_BSS_ASSOCIATED		BIT(5)
#define WPA_BSS_ANQP_FETCH_TRIED	BIT(6)

struct wpa_bss_anqp {
	unsigned int users;
#ifdef CONFIG_INTERWORKING
	struct wpabuf *venue_name;
	struct wpabuf *network_auth_type;
	struct wpabuf *roaming_consortium;
	struct wpabuf *ip_addr_type_availability;
	struct wpabuf *nai_realm;
	struct wpabuf *anqp_3gpp;
	struct wpabuf *domain_name;
#endif /* CONFIG_INTERWORKING */
#ifdef CONFIG_HS20
	struct wpabuf *hs20_operator_friendly_name;
	struct wpabuf *hs20_wan_metrics;
	struct wpabuf *hs20_connection_capability;
	struct wpabuf *hs20_operating_class;
#endif /* CONFIG_HS20 */
};

/**
 * struct wpa_bss - BSS table
 * @list: List entry for struct wpa_supplicant::bss
 * @list_id: List entry for struct wpa_supplicant::bss_id
 * @id: Unique identifier for this BSS entry
 * @scan_miss_count: Number of counts without seeing this BSS
 * @flags: information flags about the BSS/IBSS (WPA_BSS_*)
 * @last_update_idx: Index of the last scan update
 * @bssid: BSSID
 * @hessid: HESSID
 * @freq: frequency of the channel in MHz (e.g., 2412 = channel 1)
 * @beacon_int: beacon interval in TUs (host byte order)
 * @caps: capability information field in host byte order
 * @qual: signal quality
 * @noise: noise level
 * @level: signal level
 * @tsf: Timestamp of last Beacon/Probe Response frame
 * @last_update: Time of the last update (i.e., Beacon or Probe Response RX)
 * @ie_len: length of the following IE field in octets (from Probe Response)
 * @beacon_ie_len: length of the following Beacon IE field in octets
 *
 * This structure is used to store information about neighboring BSSes in
 * generic format. It is mainly updated based on scan results from the driver.
 */
struct wpa_bss {
	struct dl_list list;
	struct dl_list list_id;
	unsigned int id;
	unsigned int scan_miss_count;
	unsigned int last_update_idx;
	unsigned int flags;
	u8 bssid[ETH_ALEN];
	u8 hessid[ETH_ALEN];
	u8 ssid[32];
	size_t ssid_len;
	int freq;
	u16 beacon_int;
	u16 caps;
	int qual;
	int noise;
	int level;
	u64 tsf;
	struct os_time last_update;
	struct wpa_bss_anqp *anqp;
	size_t ie_len;
	size_t beacon_ie_len;
	/* followed by ie_len octets of IEs */
	/* followed by beacon_ie_len octets of IEs */
};

void wpa_bss_update_start(struct wpa_supplicant *wpa_s);
void wpa_bss_update_scan_res(struct wpa_supplicant *wpa_s,
			     struct wpa_scan_res *res,
			     struct os_time *fetch_time);
void wpa_bss_update_end(struct wpa_supplicant *wpa_s, struct scan_info *info,
			int new_scan);
int wpa_bss_init(struct wpa_supplicant *wpa_s);
void wpa_bss_deinit(struct wpa_supplicant *wpa_s);
void wpa_bss_flush(struct wpa_supplicant *wpa_s);
void wpa_bss_flush_by_age(struct wpa_supplicant *wpa_s, int age);
struct wpa_bss * wpa_bss_get(struct wpa_supplicant *wpa_s, const u8 *bssid,
			     const u8 *ssid, size_t ssid_len);
struct wpa_bss * wpa_bss_get_bssid(struct wpa_supplicant *wpa_s,
				   const u8 *bssid);
struct wpa_bss * wpa_bss_get_p2p_dev_addr(struct wpa_supplicant *wpa_s,
					  const u8 *dev_addr);
struct wpa_bss * wpa_bss_get_id(struct wpa_supplicant *wpa_s, unsigned int id);
struct wpa_bss * wpa_bss_get_id_range(struct wpa_supplicant *wpa_s,
				      unsigned int idf, unsigned int idl);
const u8 * wpa_bss_get_ie(const struct wpa_bss *bss, u8 ie);
const u8 * wpa_bss_get_vendor_ie(const struct wpa_bss *bss, u32 vendor_type);
struct wpabuf * wpa_bss_get_vendor_ie_multi(const struct wpa_bss *bss,
					    u32 vendor_type);
struct wpabuf * wpa_bss_get_vendor_ie_multi_beacon(const struct wpa_bss *bss,
						   u32 vendor_type);
int wpa_bss_get_max_rate(const struct wpa_bss *bss);
int wpa_bss_get_bit_rates(const struct wpa_bss *bss, u8 **rates);
struct wpa_bss_anqp * wpa_bss_anqp_alloc(void);
int wpa_bss_anqp_unshare_alloc(struct wpa_bss *bss);

#endif /* BSS_H */
