/*
    pmacct (Promiscuous mode IP Accounting package)
    pmacct is Copyright (C) 2003-2016 by Paolo Lucente
*/

/*
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
*/

/* defines */
#define PLUGIN_ID_CORE          0
#define PLUGIN_ID_MEMORY        1
#define PLUGIN_ID_PRINT         2
#define PLUGIN_ID_NFPROBE       3
#define PLUGIN_ID_SFPROBE       4
#define PLUGIN_ID_MYSQL		5 
#define PLUGIN_ID_PGSQL         6
#define PLUGIN_ID_SQLITE3       7
#define PLUGIN_ID_TEE		8
#define PLUGIN_ID_MONGODB	9
#define PLUGIN_ID_AMQP		10
#define PLUGIN_ID_KAFKA		11
#define PLUGIN_ID_UNKNOWN       -1

/* vars */
#if (!defined __PMACCTD_C) && (!defined __NFACCTD_C) && (!defined __SFACCTD_C) && (!defined __UACCTD_C) && (!defined __PMTELEMETRYD_C) && (!defined __PMACCT_CLIENT_C)
#define EXT extern
#else
#define EXT
#endif
EXT int protocols_number;
#undef EXT

/* structures */
static const struct _primitives_matrix_struct _primitives_matrix[] = {
  /* primitive, pmacctd, uacctd, nfacctd, sfacctd */
  {"L2", 1, 1, 1, 1, ""}, 
  {"cos", 1, 0, 1, 1, "Ethernet CoS, 802.1P"},
  {"etype", 1, 0, 1, 1, "Ethernet Ethertype"},
  {"src_mac", 1, 1, 1, 1, "Source MAC address"},
  {"dst_mac", 1, 1, 1, 1, "Destination MAC address"},
  {"vlan", 1, 1, 1, 1, "Ethernet VLAN, 802.1Q"},
  {"L3", 1, 1, 1, 1, ""}, 
  {"src_host", 1, 1, 1, 1, "Source IPv4/IPv6 address"}, 
  {"dst_host", 1, 1, 1, 1, "Destination IPv4/IPv6 address"},
  {"src_mask", 1, 1, 1, 1, "Source network mask"},
  {"dst_mask", 1, 1, 1, 1, "Destination network mask"},
  {"src_net", 1, 1, 1, 1, "Source IPv4/IPv6 prefix"},
  {"dst_net", 1, 1, 1, 1, "Destination IPv4/IPv6 prefix"},
  {"proto", 1, 1, 1, 1, "IP protocol"},
  {"tos", 1, 1, 1, 1, "IP ToS"},
  {"L4", 1, 1, 1, 1, ""}, 
  {"src_port", 1, 1, 1, 1, "Source TCP/UDP port"},
  {"dst_port", 1, 1, 1, 1, "Destination TCP/UDP port"},
  {"tcpflags", 1, 1, 1, 1, "TCP flags"},
  {"BGP", 1, 1, 1, 1, ""}, 
  {"src_as", 1, 1, 1, 1, "Source ASN"},
  {"dst_as", 1, 1, 1, 1, "Destination ASN"},
  {"as_path", 1, 1, 1, 1, "AS PATH"},
  {"std_comm", 1, 1, 1, 1, "Standard Communities"},
  {"ext_comm", 1, 1, 1, 1, "Extended Communities"},
  {"local_pref", 1, 1, 1, 1, "Local Preference"},
  {"med", 1, 1, 1, 1, "Multi-Exit Discriminator"},
  {"src_as_path", 1, 1, 1, 1, "Source AS PATH (via reverse BGP lookup)"},
  {"src_std_comm", 1, 1, 1, 1, "Source Standard Communities (via reverse BGP lookup)"},
  {"src_ext_comm", 1, 1, 1, 1, "Source Extended Communities (via reverse BGP lookup)"},
  {"src_local_pref", 1, 1, 1, 1, "Source Local Preference (by default via reverse BGP lookup)"},
  {"src_med", 1, 1, 1, 1, "Source MED (by default via reverse BGP lookup)"},
  {"mpls_vpn_rd", 0, 0, 1, 1, "MPLS VPN Route Distinguisher"},
  {"peer_src_as", 1, 1, 1, 1, "Source peer ASN (by default via reverse BGP lookup)"},
  {"peer_dst_as", 1, 1, 1, 1, "Destination peer ASN"},
  {"peer_dst_ip", 1, 1, 1, 1, "BGP next-hop"},
  {"NAT", 1, 1, 1, 1, ""}, 
  {"fw_event", 0, 0, 1, 0, "Firewall event ID"},
  {"nat_event", 0, 0, 1, 0, "NAT event ID"},
  {"post_nat_src_host", 0, 0, 1, 0, "Source IPv4/IPv6 address after NAT translation"},
  {"post_nat_dst_host", 0, 0, 1, 0, "Destination IPv4/IPv6 address after NAT translation"},
  {"post_nat_src_port", 0, 0, 1, 0, "Source TCP/UDP port after NAT translation"},
  {"post_nat_dst_port", 0, 0, 1, 0, "Destination TCP/UDP port after NAT translation"},
  {"MPLS", 1, 1, 1, 1, ""}, 
  {"mpls_label_bottom", 1, 1, 1, 0, "Bottom MPLS label"},
  {"mpls_label_top", 1, 1, 1, 0, "Top MPLS label"},
  {"mpls_stack_depth", 1, 1, 1, 0, "MPLS stack depth"},
  {"MISC", 1, 1, 1, 1, ""}, 
  {"class", 1, 1, 1, 1, "L7 protocol classification"},
  {"flows", 0, 0, 1, 0, "IP flows"},
  {"src_host_country", 1, 1, 1, 1, "Source IP address GeoIP resolution: country"},
  {"dst_host_country", 1, 1, 1, 1, "Destination IP address GeoIP resolution: country"},
  {"in_iface", 0, 1, 1, 1, "Input interface, SNMP ifIndex"}, 
  {"out_iface", 0, 1, 1, 1, "Output interface, SNMP ifIndex"}, 
  {"peer_src_ip", 0, 0, 1, 1, "IP address or identificator of telemetry exporting device"},
  {"pkt_len_distrib", 1, 1, 1, 1, "Packet length distribution"},
  {"sampling_rate", 1, 1, 1, 1, "Sampling rate"},
  {"tag", 1, 1, 1, 1, "Numeric tag, ie. as result of pre_tag_map evaluation"},
  {"tag2", 1, 1, 1, 1, "Numeric tag, ie. as result of pre_tag_map evaluation"},
  {"label", 1, 1, 1, 1, "String label, ie. as result of pre_tag_map evaluation"},
  {"export_proto_seqno", 0, 0, 1, 1, "Export protocol (ie. NetFlow) sequence number"},
  {"export_proto_version", 0, 0, 1, 1, "Export protocol (ie. NetFlow) version"},
  {"TIME", 1, 1, 1, 1, ""}, 
  {"timestamp_start", 0, 0, 1, 0, "Flow start time or observation time at the exporter"},
  {"timestamp_end", 0, 0, 1, 0, "Flow end time"},
  {"timestamp_arrival", 1, 1, 1, 1, "Observation time at the collector"},
  {"", 0, 0, 0, 0, ""}
};

static const struct _protocols_struct _protocols[] = {
  {"ip", 0},
  {"icmp", 1},
  {"igmp", 2},
  {"ggp", 3},
  {"4", 4},
  {"5", 5},
  {"tcp", 6},
  {"7", 7},
  {"egp", 8},
  {"igp", 9},
  {"10", 10},
  {"11", 11},
  {"12", 12},
  {"13", 13},
  {"14", 14},
  {"15", 15},
  {"16", 16},
  {"udp", 17},
  {"mux", 18},
  {"19", 19},
  {"20", 20},
  {"21", 21},
  {"22", 22},
  {"23", 23},
  {"24", 24},
  {"25", 25},
  {"26", 26},
  {"27", 27},
  {"28", 28},
  {"29", 29},
  {"30", 30},
  {"31", 31},
  {"32", 32},
  {"33", 33},
  {"34", 34},
  {"35", 35},
  {"36", 36},
  {"37", 37},
  {"38", 38}, 
  {"39", 39},
  {"40", 40},
  {"ipv6", 41},
  {"42", 42},
  {"ipv6-route", 43},
  {"ipv6-frag", 44},
  {"45", 45},
  {"rsvp", 46},
  {"gre", 47},
  {"48", 48},
  {"49", 49},
  {"ipv6-crypt", 50}, 
  {"ipv6-auth", 51},
  {"52", 52}, 
  {"53", 53},  
  {"54", 54}, 
  {"mobile", 55},   
  {"tlsp", 56},
  {"57", 57}, 
  {"ipv6-icmp", 58},    
  {"ipv6-nonxt", 59},
  {"ipv6-opts", 60},
  {"61", 61},
  {"62", 62},
  {"63", 63},
  {"64", 64},     
  {"65", 65},  
  {"66", 66},
  {"67", 67}, 
  {"68", 68},
  {"69", 69},   
  {"70", 70},
  {"71", 71},  
  {"72", 72}, 
  {"73", 73},
  {"74", 74},
  {"75", 75},
  {"76", 76},  
  {"77", 77},
  {"78", 78}, 
  {"79", 79},  
  {"iso-ip", 80},
  {"81", 81}, 
  {"82", 82},
  {"vines", 83},
  {"84", 84},
  {"85", 85}, 
  {"86", 86},
  {"87", 87},  
  {"eigrp", 88},   
  {"ospf", 89},
  {"90", 90}, 
  {"larp", 91},
  {"92", 92}, 
  {"ax.25", 93},   
  {"ipip", 94},
  {"95", 95},
  {"96", 96},
  {"97", 97},    
  {"encap", 98},
  {"99", 99},
  {"100", 100},  
  {"101", 101}, 
  {"pnni", 102},
  {"pim", 103},
  {"104", 104},
  {"105", 105},  
  {"106", 106},
  {"107", 107},
  {"IPcomp", 108}, 
  {"109", 109},
  {"110", 110},  
  {"ipx-in-ip", 111},
  {"vrrp", 112},
  {"113", 113}, 
  {"114", 114},
  {"l2tp", 115},   
  {"116", 116},
  {"117", 117}, 
  {"118", 118},
  {"119", 119},
  {"120", 120},  
  {"121", 121}, 
  {"122", 122},
  {"123", 123},
  {"isis", 124},
  {"125", 125},  
  {"126", 126},
  {"127", 127},
  {"128", 128}, 
  {"129", 129},
  {"130", 130},
  {"131", 131}, 
  {"sctp", 132},
  {"fc", 133},
  {"", -1},
};

/* cps = custom primitive semantics */
static const char *cps_type[] = {
  "",
  "u",
  "x",
  "s",
  "s",
  "s",
  "s"
};

static const int cps_flen[] = {
  0,
  3,
  5,
  0,
  10,
  0,
  0,
  0,
  20
};

#if defined __PMACCTD_C || defined __UACCTD_C
static struct _devices_struct _devices[] = {
#if defined DLT_LOOP
  {null_handler, DLT_LOOP},
#endif
  {null_handler, DLT_NULL},
  {eth_handler, DLT_EN10MB},
  {ppp_handler, DLT_PPP},
  {fddi_handler, DLT_FDDI},
  {tr_handler, DLT_IEEE802},
#if defined DLT_IEEE802_11
  {ieee_802_11_handler, DLT_IEEE802_11}, 
#endif
#if defined DLT_LINUX_SLL
  {sll_handler, DLT_LINUX_SLL},
#endif
#if defined DLT_RAW
  {raw_handler, DLT_RAW},
#endif
#if defined DLT_C_HDLC
  {chdlc_handler, DLT_C_HDLC},
#endif
#ifdef DLT_HDLC
  {chdlc_handler, DLT_HDLC},
#endif
  {NULL, -1},
};
#endif

#ifdef __CFG_C
static const struct _dictionary_line dictionary[] = {
  {"debug", cfg_key_debug},
  {"debug_internal_msg", cfg_key_debug_internal_msg},
  {"syslog", cfg_key_syslog},
  {"logfile", cfg_key_logfile},
  {"pidfile", cfg_key_pidfile},
  {"daemonize", cfg_key_daemonize},
  {"aggregate", cfg_key_aggregate},
  {"aggregate_primitives", cfg_key_aggregate_primitives},
  {"snaplen", cfg_key_snaplen},
  {"aggregate_filter", cfg_key_aggregate_filter},
  {"promisc", cfg_key_promisc},
  {"pcap_filter", cfg_key_pcap_filter},
  {"core_proc_name", cfg_key_proc_name},
  {"proc_priority", cfg_key_proc_priority},
  {"pmacctd_as", cfg_key_nfacctd_as_new},
  {"uacctd_as", cfg_key_nfacctd_as_new},
  {"pmacctd_net", cfg_key_nfacctd_net},
  {"uacctd_net", cfg_key_nfacctd_net},
  {"use_ip_next_hop", cfg_key_use_ip_next_hop},
  {"thread_stack", cfg_key_thread_stack},
  {"plugins", NULL},
  {"plugin_pipe_size", cfg_key_plugin_pipe_size},
  {"plugin_pipe_backlog", cfg_key_plugin_pipe_backlog},
  {"plugin_pipe_check_core_pid", cfg_key_plugin_pipe_check_core_pid},
  {"plugin_pipe_amqp", cfg_key_plugin_pipe_amqp},
  {"plugin_pipe_amqp_user", cfg_key_plugin_pipe_amqp_user},
  {"plugin_pipe_amqp_passwd", cfg_key_plugin_pipe_amqp_passwd},
  {"plugin_pipe_amqp_exchange", cfg_key_plugin_pipe_amqp_exchange},
  {"plugin_pipe_amqp_host", cfg_key_plugin_pipe_amqp_host},
  {"plugin_pipe_amqp_vhost", cfg_key_plugin_pipe_amqp_vhost},
  {"plugin_pipe_amqp_routing_key", cfg_key_plugin_pipe_amqp_routing_key},
  {"plugin_pipe_amqp_retry", cfg_key_plugin_pipe_amqp_retry},
  {"plugin_pipe_kafka", cfg_key_plugin_pipe_kafka},
  {"plugin_pipe_kafka_broker_host", cfg_key_plugin_pipe_kafka_broker_host},
  {"plugin_pipe_kafka_broker_port", cfg_key_plugin_pipe_kafka_broker_port},
  {"plugin_pipe_kafka_topic", cfg_key_plugin_pipe_kafka_topic},
  {"plugin_pipe_kafka_partition", cfg_key_plugin_pipe_kafka_partition},
  {"plugin_pipe_kafka_retry", cfg_key_plugin_pipe_kafka_retry},
  {"plugin_buffer_size", cfg_key_plugin_buffer_size},
  {"interface", cfg_key_interface},
  {"interface_wait", cfg_key_interface_wait},
  {"files_umask", cfg_key_files_umask},
  {"files_uid", cfg_key_files_uid},
  {"files_gid", cfg_key_files_gid},
  {"savefile_wait", cfg_key_savefile_wait},
  {"networks_mask", cfg_key_networks_mask},
  {"networks_file", cfg_key_networks_file},
  {"networks_file_filter", cfg_key_networks_file_filter},
  {"networks_file_no_lpm", cfg_key_networks_file_no_lpm},
  {"networks_cache_entries", cfg_key_networks_cache_entries},
  {"ports_file", cfg_key_ports_file},
  {"timestamps_secs", cfg_key_timestamps_secs},
  {"timestamps_since_epoch", cfg_key_timestamps_since_epoch},
  {"imt_path", cfg_key_imt_path},
  {"imt_passwd", cfg_key_imt_passwd},
  {"imt_buckets", cfg_key_imt_buckets},
  {"imt_mem_pools_number", cfg_key_imt_mem_pools_number},
  {"imt_mem_pools_size", cfg_key_imt_mem_pools_size},
  {"sql_db", cfg_key_sql_db},
  {"sql_table", cfg_key_sql_table},
  {"sql_table_schema", cfg_key_sql_table_schema},
  {"sql_table_version", cfg_key_sql_table_version},
  {"sql_table_type", cfg_key_sql_table_type},
  {"sql_host", cfg_key_sql_host},
  {"sql_data", cfg_key_sql_data},
  {"sql_backup_host", cfg_key_sql_recovery_backup_host}, /* obsolete */
  {"sql_user", cfg_key_sql_user},
  {"sql_passwd", cfg_key_sql_passwd},
  {"sql_refresh_time", cfg_key_sql_refresh_time},
  {"sql_startup_delay", cfg_key_sql_startup_delay},
  {"sql_optimize_clauses", cfg_key_sql_optimize_clauses},
  {"sql_history", cfg_key_sql_history},
  {"sql_history_offset", cfg_key_sql_history_offset},
  {"sql_history_roundoff", cfg_key_sql_history_roundoff},
  {"sql_history_since_epoch", cfg_key_timestamps_since_epoch}, // legacy
  {"sql_recovery_backup_host", cfg_key_sql_recovery_backup_host},
  {"sql_delimiter", cfg_key_sql_delimiter},
  {"sql_max_writers", cfg_key_sql_max_writers},
  {"sql_trigger_exec", cfg_key_sql_trigger_exec},
  {"sql_trigger_time", cfg_key_sql_trigger_time},
  {"sql_cache_entries", cfg_key_sql_cache_entries},
  {"sql_dont_try_update", cfg_key_sql_dont_try_update},
  {"sql_preprocess", cfg_key_sql_preprocess},
  {"sql_preprocess_type", cfg_key_sql_preprocess_type},
  {"sql_multi_values", cfg_key_sql_multi_values},
  {"sql_aggressive_classification", cfg_key_sql_aggressive_classification},
  {"sql_locking_style", cfg_key_sql_locking_style},
  {"sql_use_copy", cfg_key_sql_use_copy},
  {"sql_num_protos", cfg_key_num_protos},
  {"sql_num_hosts", cfg_key_num_hosts},
  {"print_refresh_time", cfg_key_sql_refresh_time},
  {"print_cache_entries", cfg_key_print_cache_entries},
  {"print_markers", cfg_key_print_markers},
  {"print_output", cfg_key_print_output},
  {"print_output_file", cfg_key_print_output_file},
  {"print_output_file_append", cfg_key_print_output_file_append},
  {"print_output_lock_file", cfg_key_print_output_lock_file},
  {"print_output_separator", cfg_key_print_output_separator},
  {"print_latest_file", cfg_key_print_latest_file},
  {"print_num_protos", cfg_key_num_protos},
  {"print_time_roundoff", cfg_key_sql_history_roundoff},
  {"print_trigger_exec", cfg_key_sql_trigger_exec},
  {"print_history", cfg_key_sql_history},
  {"print_history_offset", cfg_key_sql_history_offset},
  {"print_history_roundoff", cfg_key_sql_history_roundoff},
  {"print_max_writers", cfg_key_sql_max_writers},
  {"print_preprocess", cfg_key_sql_preprocess},
  {"print_preprocess_type", cfg_key_sql_preprocess_type},
  {"print_startup_delay", cfg_key_sql_startup_delay},
  {"mongo_host", cfg_key_sql_host},
  {"mongo_table", cfg_key_sql_table},
  {"mongo_user", cfg_key_sql_user},
  {"mongo_passwd", cfg_key_sql_passwd},
  {"mongo_refresh_time", cfg_key_sql_refresh_time},
  {"mongo_cache_entries", cfg_key_print_cache_entries},
  {"mongo_history", cfg_key_sql_history},
  {"mongo_history_offset", cfg_key_sql_history_offset},
  {"mongo_history_roundoff", cfg_key_sql_history_roundoff},
  {"mongo_time_roundoff", cfg_key_sql_history_roundoff},
  {"mongo_trigger_exec", cfg_key_sql_trigger_exec},
  {"mongo_insert_batch", cfg_key_mongo_insert_batch},
  {"mongo_indexes_file", cfg_key_sql_table_schema},
  {"mongo_max_writers", cfg_key_sql_max_writers},
  {"mongo_preprocess", cfg_key_sql_preprocess},
  {"mongo_preprocess_type", cfg_key_sql_preprocess_type},
  {"mongo_startup_delay", cfg_key_sql_startup_delay},
  {"mongo_num_protos", cfg_key_num_protos},
  {"amqp_refresh_time", cfg_key_sql_refresh_time},
  {"amqp_history", cfg_key_sql_history},
  {"amqp_history_offset", cfg_key_sql_history_offset},
  {"amqp_history_roundoff", cfg_key_sql_history_roundoff},
  {"amqp_time_roundoff", cfg_key_sql_history_roundoff},
  {"amqp_host", cfg_key_sql_host},
  {"amqp_user", cfg_key_sql_user},
  {"amqp_passwd", cfg_key_sql_passwd},
  {"amqp_exchange", cfg_key_sql_db},
  {"amqp_exchange_type", cfg_key_amqp_exchange_type},
  {"amqp_routing_key", cfg_key_sql_table},
  {"amqp_routing_key_rr", cfg_key_amqp_routing_key_rr},
  {"amqp_persistent_msg", cfg_key_amqp_persistent_msg},
  {"amqp_frame_max", cfg_key_amqp_frame_max},
  {"amqp_cache_entries", cfg_key_print_cache_entries},
  {"amqp_max_writers", cfg_key_sql_max_writers},
  {"amqp_preprocess", cfg_key_sql_preprocess},
  {"amqp_preprocess_type", cfg_key_sql_preprocess_type},
  {"amqp_startup_delay", cfg_key_sql_startup_delay},
  {"amqp_heartbeat_interval", cfg_key_amqp_heartbeat_interval},
  {"amqp_multi_values", cfg_key_sql_multi_values},
  {"amqp_num_protos", cfg_key_num_protos},
  {"amqp_vhost", cfg_key_amqp_vhost},
  {"kafka_refresh_time", cfg_key_sql_refresh_time},
  {"kafka_history", cfg_key_sql_history},
  {"kafka_history_offset", cfg_key_sql_history_offset},
  {"kafka_history_roundoff", cfg_key_sql_history_roundoff},
  {"kafka_broker_host", cfg_key_sql_host},
  {"kafka_broker_port", cfg_key_kafka_broker_port},
  {"kafka_topic", cfg_key_sql_table},
  {"kafka_topic_rr", cfg_key_amqp_routing_key_rr},
  {"kafka_partition", cfg_key_kafka_partition},
  {"kafka_cache_entries", cfg_key_print_cache_entries},
  {"kafka_max_writers", cfg_key_sql_max_writers},
  {"kafka_preprocess", cfg_key_sql_preprocess},
  {"kafka_preprocess_type", cfg_key_sql_preprocess_type},
  {"kafka_startup_delay", cfg_key_sql_startup_delay},
  {"kafka_multi_values", cfg_key_sql_multi_values},
  {"kafka_num_protos", cfg_key_num_protos},
  {"nfacctd_proc_name", cfg_key_proc_name},
  {"nfacctd_port", cfg_key_nfacctd_port},
  {"nfacctd_ip", cfg_key_nfacctd_ip},
  {"nfacctd_allow_file", cfg_key_nfacctd_allow_file},
  {"nfacctd_time_secs", cfg_key_nfacctd_time_secs},
  {"nfacctd_time_new", cfg_key_nfacctd_time_new},
  {"nfacctd_as_new", cfg_key_nfacctd_as_new},
  {"nfacctd_as", cfg_key_nfacctd_as_new},
  {"nfacctd_net", cfg_key_nfacctd_net},
  {"nfacctd_mcast_groups", cfg_key_nfacctd_mcast_groups},
  {"nfacctd_peer_as", cfg_key_nfprobe_peer_as},
  {"nfacctd_pipe_size", cfg_key_nfacctd_pipe_size},
  {"nfacctd_pro_rating", cfg_key_nfacctd_pro_rating},
  {"nfacctd_account_options", cfg_key_nfacctd_account_options},
  {"nfacctd_stitching", cfg_key_nfacctd_stitching},
  {"nfacctd_ext_sampling_rate", cfg_key_pmacctd_ext_sampling_rate},
  {"nfacctd_renormalize", cfg_key_sfacctd_renormalize},
  {"nfacctd_disable_checks", cfg_key_nfacctd_disable_checks},
  {"pmacctd_proc_name", cfg_key_proc_name},
  {"pmacctd_force_frag_handling", cfg_key_pmacctd_force_frag_handling},
  {"pmacctd_frag_buffer_size", cfg_key_pmacctd_frag_buffer_size},
  {"pmacctd_flow_buffer_size", cfg_key_pmacctd_flow_buffer_size},
  {"pmacctd_flow_buffer_buckets", cfg_key_pmacctd_flow_buffer_buckets},
  {"pmacctd_conntrack_buffer_size", cfg_key_pmacctd_conntrack_buffer_size},
  {"pmacctd_flow_lifetime", cfg_key_pmacctd_flow_lifetime},
  {"pmacctd_flow_tcp_lifetime", cfg_key_pmacctd_flow_tcp_lifetime},
  {"pmacctd_ext_sampling_rate", cfg_key_pmacctd_ext_sampling_rate},
  {"pmacctd_pipe_size", cfg_key_nfacctd_pipe_size},
  {"pmacctd_stitching", cfg_key_nfacctd_stitching},
  {"pmacctd_renormalize", cfg_key_sfacctd_renormalize},
  {"pmacctd_nonroot", cfg_key_pmacctd_nonroot},
  {"uacctd_proc_name", cfg_key_proc_name},
  {"uacctd_force_frag_handling", cfg_key_pmacctd_force_frag_handling},
  {"uacctd_frag_buffer_size", cfg_key_pmacctd_frag_buffer_size},
  {"uacctd_flow_buffer_size", cfg_key_pmacctd_flow_buffer_size},
  {"uacctd_flow_buffer_buckets", cfg_key_pmacctd_flow_buffer_buckets},
  {"uacctd_conntrack_buffer_size", cfg_key_pmacctd_conntrack_buffer_size},
  {"uacctd_flow_lifetime", cfg_key_pmacctd_flow_lifetime},
  {"uacctd_flow_tcp_lifetime", cfg_key_pmacctd_flow_tcp_lifetime},
  {"uacctd_ext_sampling_rate", cfg_key_pmacctd_ext_sampling_rate},
  {"uacctd_stitching", cfg_key_nfacctd_stitching},
  {"uacctd_renormalize", cfg_key_sfacctd_renormalize},
  {"telemetry_daemon", cfg_key_telemetry_daemon},
  {"telemetry_daemon_proc_name", cfg_key_proc_name},
  {"telemetry_daemon_port_tcp", cfg_key_telemetry_port_tcp},
  {"telemetry_daemon_port_udp", cfg_key_telemetry_port_udp},
  {"telemetry_daemon_ip", cfg_key_telemetry_ip},
  {"telemetry_daemon_decoder", cfg_key_telemetry_decoder},
  {"telemetry_daemon_max_peers", cfg_key_telemetry_max_peers},
  {"telemetry_daemon_udp_timeout", cfg_key_telemetry_udp_timeout},
  {"telemetry_daemon_allow_file", cfg_key_telemetry_allow_file},
  {"telemetry_daemon_pipe_size", cfg_key_telemetry_pipe_size},
  {"telemetry_daemon_ipprec", cfg_key_telemetry_ip_precedence},
  {"telemetry_daemon_msglog_output", cfg_key_telemetry_msglog_output},
  {"telemetry_daemon_msglog_file", cfg_key_telemetry_msglog_file},
  {"telemetry_daemon_msglog_amqp_host", cfg_key_telemetry_msglog_amqp_host},
  {"telemetry_daemon_msglog_amqp_vhost", cfg_key_telemetry_msglog_amqp_vhost},
  {"telemetry_daemon_msglog_amqp_user", cfg_key_telemetry_msglog_amqp_user},
  {"telemetry_daemon_msglog_amqp_passwd", cfg_key_telemetry_msglog_amqp_passwd},
  {"telemetry_daemon_msglog_amqp_exchange", cfg_key_telemetry_msglog_amqp_exchange},
  {"telemetry_daemon_msglog_amqp_exchange_type", cfg_key_telemetry_msglog_amqp_exchange_type},
  {"telemetry_daemon_msglog_amqp_routing_key", cfg_key_telemetry_msglog_amqp_routing_key},
  {"telemetry_daemon_msglog_amqp_routing_key_rr", cfg_key_telemetry_msglog_amqp_routing_key_rr},
  {"telemetry_daemon_msglog_amqp_persistent_msg", cfg_key_telemetry_msglog_amqp_persistent_msg},
  {"telemetry_daemon_msglog_amqp_frame_max", cfg_key_telemetry_msglog_amqp_frame_max},
  {"telemetry_daemon_msglog_amqp_heartbeat_interval", cfg_key_telemetry_msglog_amqp_heartbeat_interval},
  {"telemetry_daemon_msglog_amqp_retry", cfg_key_telemetry_msglog_amqp_retry},
  {"telemetry_daemon_msglog_kafka_broker_host", cfg_key_telemetry_msglog_kafka_broker_host},
  {"telemetry_daemon_msglog_kafka_broker_port", cfg_key_telemetry_msglog_kafka_broker_port},
  {"telemetry_daemon_msglog_kafka_topic", cfg_key_telemetry_msglog_kafka_topic},
  {"telemetry_daemon_msglog_kafka_topic_rr", cfg_key_telemetry_msglog_kafka_topic_rr},
  {"telemetry_daemon_msglog_kafka_partition", cfg_key_telemetry_msglog_kafka_partition},
  {"telemetry_daemon_msglog_kafka_retry", cfg_key_telemetry_msglog_kafka_retry},
  {"telemetry_dump_output", cfg_key_telemetry_dump_output},
  {"telemetry_dump_file", cfg_key_telemetry_dump_file},
  {"telemetry_dump_latest_file", cfg_key_telemetry_dump_latest_file},
  {"telemetry_dump_refresh_time", cfg_key_telemetry_dump_refresh_time},
  {"telemetry_dump_amqp_host", cfg_key_telemetry_dump_amqp_host},
  {"telemetry_dump_amqp_vhost", cfg_key_telemetry_dump_amqp_vhost},
  {"telemetry_dump_amqp_user", cfg_key_telemetry_dump_amqp_user},
  {"telemetry_dump_amqp_passwd", cfg_key_telemetry_dump_amqp_passwd},
  {"telemetry_dump_amqp_exchange", cfg_key_telemetry_dump_amqp_exchange},
  {"telemetry_dump_amqp_exchange_type", cfg_key_telemetry_dump_amqp_exchange_type},
  {"telemetry_dump_amqp_routing_key", cfg_key_telemetry_dump_amqp_routing_key},
  {"telemetry_dump_amqp_routing_key_rr", cfg_key_telemetry_dump_amqp_routing_key_rr},
  {"telemetry_dump_amqp_persistent_msg", cfg_key_telemetry_dump_amqp_persistent_msg},
  {"telemetry_dump_amqp_frame_max", cfg_key_telemetry_dump_amqp_frame_max},
  {"telemetry_dump_amqp_heartbeat_interval", cfg_key_telemetry_dump_amqp_heartbeat_interval},
  {"telemetry_dump_kafka_broker_host", cfg_key_telemetry_dump_kafka_broker_host},
  {"telemetry_dump_kafka_broker_port", cfg_key_telemetry_dump_kafka_broker_port},
  {"telemetry_dump_kafka_topic", cfg_key_telemetry_dump_kafka_topic},
  {"telemetry_dump_kafka_topic_rr", cfg_key_telemetry_dump_kafka_topic_rr},
  {"telemetry_dump_kafka_partition", cfg_key_telemetry_dump_kafka_partition},
  {"pcap_savefile", cfg_key_pcap_savefile},
  {"refresh_maps", cfg_key_maps_refresh}, // legacy
  {"maps_refresh", cfg_key_maps_refresh},
  {"maps_index", cfg_key_maps_index},
  {"maps_entries", cfg_key_maps_entries},
  {"maps_row_len", cfg_key_maps_row_len},
  {"pre_tag_map", cfg_key_pre_tag_map},	
  {"pre_tag_map_entries", cfg_key_maps_entries}, // legacy	
  {"pre_tag_filter", cfg_key_pre_tag_filter},
  {"pre_tag2_filter", cfg_key_pre_tag2_filter},
  {"pre_tag_label_filter", cfg_key_pre_tag_label_filter},
  {"post_tag", cfg_key_post_tag},
  {"post_tag2", cfg_key_post_tag2},
  {"sampling_rate", cfg_key_sampling_rate},
  {"sampling_map", cfg_key_sampling_map},	
  {"sfacctd_proc_name", cfg_key_proc_name},
  {"sfacctd_port", cfg_key_nfacctd_port},
  {"sfacctd_ip", cfg_key_nfacctd_ip},
  {"sfacctd_allow_file", cfg_key_nfacctd_allow_file},
  {"sfacctd_as_new", cfg_key_nfacctd_as_new},
  {"sfacctd_as", cfg_key_nfacctd_as_new},
  {"sfacctd_net", cfg_key_nfacctd_net},
  {"sfacctd_peer_as", cfg_key_nfprobe_peer_as},
  {"sfacctd_pipe_size", cfg_key_nfacctd_pipe_size},
  {"sfacctd_renormalize", cfg_key_sfacctd_renormalize},
  {"sfacctd_disable_checks", cfg_key_nfacctd_disable_checks},
  {"sfacctd_mcast_groups", cfg_key_nfacctd_mcast_groups},
  {"sfacctd_stitching", cfg_key_nfacctd_stitching},
  {"sfacctd_ext_sampling_rate", cfg_key_pmacctd_ext_sampling_rate},
  {"sfacctd_counter_output", cfg_key_sfacctd_counter_output},
  {"sfacctd_counter_file", cfg_key_sfacctd_counter_file},
  {"sfacctd_counter_amqp_host", cfg_key_sfacctd_counter_amqp_host},
  {"sfacctd_counter_amqp_vhost", cfg_key_sfacctd_counter_amqp_vhost},
  {"sfacctd_counter_amqp_user", cfg_key_sfacctd_counter_amqp_user},
  {"sfacctd_counter_amqp_passwd", cfg_key_sfacctd_counter_amqp_passwd},
  {"sfacctd_counter_amqp_exchange", cfg_key_sfacctd_counter_amqp_exchange},
  {"sfacctd_counter_amqp_exchange_type", cfg_key_sfacctd_counter_amqp_exchange_type},
  {"sfacctd_counter_amqp_routing_key", cfg_key_sfacctd_counter_amqp_routing_key},
  {"sfacctd_counter_amqp_persistent_msg", cfg_key_sfacctd_counter_amqp_persistent_msg},
  {"sfacctd_counter_amqp_frame_max", cfg_key_sfacctd_counter_amqp_frame_max},
  {"sfacctd_counter_amqp_heartbeat_interval", cfg_key_sfacctd_counter_amqp_heartbeat_interval},
  {"sfacctd_counter_amqp_retry", cfg_key_sfacctd_counter_amqp_retry},
  {"sfacctd_counter_kafka_broker_host", cfg_key_sfacctd_counter_kafka_broker_host},
  {"sfacctd_counter_kafka_broker_port", cfg_key_sfacctd_counter_kafka_broker_port},
  {"sfacctd_counter_kafka_topic", cfg_key_sfacctd_counter_kafka_topic},
  {"sfacctd_counter_kafka_partition", cfg_key_sfacctd_counter_kafka_partition},
  {"sfacctd_counter_kafka_retry", cfg_key_sfacctd_counter_kafka_retry},
  {"classifiers", cfg_key_classifiers},
  {"classifier_tentatives", cfg_key_classifier_tentatives},
  {"classifier_table_num", cfg_key_classifier_table_num},
  {"nfprobe_timeouts", cfg_key_nfprobe_timeouts},
  {"nfprobe_hoplimit", cfg_key_nfprobe_hoplimit},
  {"nfprobe_maxflows", cfg_key_nfprobe_maxflows},
  {"nfprobe_receiver", cfg_key_nfprobe_receiver},
  {"nfprobe_engine", cfg_key_nfprobe_engine},
  {"nfprobe_version", cfg_key_nfprobe_version},
  {"nfprobe_peer_as", cfg_key_nfprobe_peer_as},
  {"nfprobe_source_ip", cfg_key_nfprobe_source_ip},
  {"nfprobe_ipprec", cfg_key_nfprobe_ip_precedence},
  {"nfprobe_direction", cfg_key_nfprobe_direction},
  {"nfprobe_ifindex", cfg_key_nfprobe_ifindex},
  {"sfprobe_receiver", cfg_key_sfprobe_receiver},
  {"sfprobe_agentip", cfg_key_sfprobe_agentip},
  {"sfprobe_agentsubid", cfg_key_sfprobe_agentsubid},
  {"sfprobe_peer_as", cfg_key_nfprobe_peer_as},
  {"sfprobe_ipprec", cfg_key_nfprobe_ip_precedence},
  {"sfprobe_direction", cfg_key_nfprobe_direction},
  {"sfprobe_ifindex", cfg_key_nfprobe_ifindex},
  {"sfprobe_ifspeed", cfg_key_sfprobe_ifspeed},
  {"tee_receiver", cfg_key_nfprobe_receiver},
  {"tee_receivers", cfg_key_tee_receivers},
  {"tee_source_ip", cfg_key_nfprobe_source_ip},
  {"tee_transparent", cfg_key_tee_transparent},
  {"tee_max_receivers", cfg_key_tee_max_receivers},
  {"tee_max_receiver_pools", cfg_key_tee_max_receiver_pools},
  {"tee_ipprec", cfg_key_nfprobe_ip_precedence},
  {"tee_pipe_size", cfg_key_tee_pipe_size},
  {"bgp_daemon", cfg_key_nfacctd_bgp},
  {"bgp_daemon_ip", cfg_key_nfacctd_bgp_ip},
  {"bgp_daemon_id", cfg_key_nfacctd_bgp_id},
  {"bgp_daemon_port", cfg_key_nfacctd_bgp_port},
  {"bgp_daemon_pipe_size", cfg_key_nfacctd_bgp_pipe_size},
  {"bgp_daemon_max_peers", cfg_key_nfacctd_bgp_max_peers},
  {"bgp_daemon_msglog_output", cfg_key_nfacctd_bgp_msglog_output},
  {"bgp_daemon_msglog_file", cfg_key_nfacctd_bgp_msglog_file},
  {"bgp_daemon_msglog_amqp_host", cfg_key_nfacctd_bgp_msglog_amqp_host},
  {"bgp_daemon_msglog_amqp_vhost", cfg_key_nfacctd_bgp_msglog_amqp_vhost},
  {"bgp_daemon_msglog_amqp_user", cfg_key_nfacctd_bgp_msglog_amqp_user},
  {"bgp_daemon_msglog_amqp_passwd", cfg_key_nfacctd_bgp_msglog_amqp_passwd},
  {"bgp_daemon_msglog_amqp_exchange", cfg_key_nfacctd_bgp_msglog_amqp_exchange},
  {"bgp_daemon_msglog_amqp_exchange_type", cfg_key_nfacctd_bgp_msglog_amqp_exchange_type},
  {"bgp_daemon_msglog_amqp_routing_key", cfg_key_nfacctd_bgp_msglog_amqp_routing_key},
  {"bgp_daemon_msglog_amqp_routing_key_rr", cfg_key_nfacctd_bgp_msglog_amqp_routing_key_rr},
  {"bgp_daemon_msglog_amqp_persistent_msg", cfg_key_nfacctd_bgp_msglog_amqp_persistent_msg},
  {"bgp_daemon_msglog_amqp_frame_max", cfg_key_nfacctd_bgp_msglog_amqp_frame_max},
  {"bgp_daemon_msglog_amqp_heartbeat_interval", cfg_key_nfacctd_bgp_msglog_amqp_heartbeat_interval},
  {"bgp_daemon_msglog_amqp_retry", cfg_key_nfacctd_bgp_msglog_amqp_retry},
  {"bgp_daemon_msglog_kafka_broker_host", cfg_key_nfacctd_bgp_msglog_kafka_broker_host},
  {"bgp_daemon_msglog_kafka_broker_port", cfg_key_nfacctd_bgp_msglog_kafka_broker_port},
  {"bgp_daemon_msglog_kafka_topic", cfg_key_nfacctd_bgp_msglog_kafka_topic},
  {"bgp_daemon_msglog_kafka_topic_rr", cfg_key_nfacctd_bgp_msglog_kafka_topic_rr},
  {"bgp_daemon_msglog_kafka_partition", cfg_key_nfacctd_bgp_msglog_kafka_partition},
  {"bgp_daemon_msglog_kafka_retry", cfg_key_nfacctd_bgp_msglog_kafka_retry},
  {"bgp_daemon_allow_file", cfg_key_nfacctd_bgp_allow_file},
  {"bgp_daemon_ipprec", cfg_key_nfacctd_bgp_ip_precedence},
  {"bgp_daemon_md5_file", cfg_key_nfacctd_bgp_md5_file},
  {"bgp_daemon_batch", cfg_key_nfacctd_bgp_batch},
  {"bgp_daemon_batch_interval", cfg_key_nfacctd_bgp_batch_interval},
  {"bgp_aspath_radius", cfg_key_nfacctd_bgp_aspath_radius},
  {"bgp_stdcomm_pattern", cfg_key_nfacctd_bgp_stdcomm_pattern},
  {"bgp_extcomm_pattern", cfg_key_nfacctd_bgp_extcomm_pattern},
  {"bgp_stdcomm_pattern_to_asn", cfg_key_nfacctd_bgp_stdcomm_pattern_to_asn},
  {"bgp_peer_as_skip_subas", cfg_key_nfacctd_bgp_peer_as_skip_subas},
  {"bgp_peer_src_as_map", cfg_key_nfacctd_bgp_peer_src_as_map},
  {"bgp_src_local_pref_map", cfg_key_nfacctd_bgp_src_local_pref_map},
  {"bgp_src_med_map", cfg_key_nfacctd_bgp_src_med_map},
  {"bgp_peer_src_as_type", cfg_key_nfacctd_bgp_peer_src_as_type},
  {"bgp_src_std_comm_type", cfg_key_nfacctd_bgp_src_std_comm_type},
  {"bgp_src_ext_comm_type", cfg_key_nfacctd_bgp_src_ext_comm_type},
  {"bgp_src_as_path_type", cfg_key_nfacctd_bgp_src_as_path_type},
  {"bgp_src_local_pref_type", cfg_key_nfacctd_bgp_src_local_pref_type},
  {"bgp_src_med_type", cfg_key_nfacctd_bgp_src_med_type},
  {"bgp_agent_map", cfg_key_nfacctd_bgp_to_agent_map},
  {"bgp_follow_default", cfg_key_nfacctd_bgp_follow_default},
  {"bgp_follow_nexthop", cfg_key_nfacctd_bgp_follow_nexthop},
  {"bgp_neighbors_file", cfg_key_nfacctd_bgp_neighbors_file},
  {"bgp_table_peer_buckets", cfg_key_nfacctd_bgp_table_peer_buckets},
  {"bgp_table_per_peer_buckets", cfg_key_nfacctd_bgp_table_per_peer_buckets},
  {"bgp_table_attr_hash_buckets", cfg_key_nfacctd_bgp_table_attr_hash_buckets},
  {"bgp_table_per_peer_hash", cfg_key_nfacctd_bgp_table_per_peer_hash},
  {"bgp_table_dump_output", cfg_key_nfacctd_bgp_table_dump_output},
  {"bgp_table_dump_file", cfg_key_nfacctd_bgp_table_dump_file},
  {"bgp_table_dump_latest_file", cfg_key_nfacctd_bgp_table_dump_latest_file},
  {"bgp_table_dump_refresh_time", cfg_key_nfacctd_bgp_table_dump_refresh_time},
  {"bgp_table_dump_amqp_host", cfg_key_nfacctd_bgp_table_dump_amqp_host},
  {"bgp_table_dump_amqp_vhost", cfg_key_nfacctd_bgp_table_dump_amqp_vhost},
  {"bgp_table_dump_amqp_user", cfg_key_nfacctd_bgp_table_dump_amqp_user},
  {"bgp_table_dump_amqp_passwd", cfg_key_nfacctd_bgp_table_dump_amqp_passwd},
  {"bgp_table_dump_amqp_exchange", cfg_key_nfacctd_bgp_table_dump_amqp_exchange},
  {"bgp_table_dump_amqp_exchange_type", cfg_key_nfacctd_bgp_table_dump_amqp_exchange_type},
  {"bgp_table_dump_amqp_routing_key", cfg_key_nfacctd_bgp_table_dump_amqp_routing_key},
  {"bgp_table_dump_amqp_routing_key_rr", cfg_key_nfacctd_bgp_table_dump_amqp_routing_key_rr},
  {"bgp_table_dump_amqp_persistent_msg", cfg_key_nfacctd_bgp_table_dump_amqp_persistent_msg},
  {"bgp_table_dump_amqp_frame_max", cfg_key_nfacctd_bgp_table_dump_amqp_frame_max},
  {"bgp_table_dump_amqp_heartbeat_interval", cfg_key_nfacctd_bgp_table_dump_amqp_heartbeat_interval},
  {"bgp_table_dump_kafka_broker_host", cfg_key_nfacctd_bgp_table_dump_kafka_broker_host},
  {"bgp_table_dump_kafka_broker_port", cfg_key_nfacctd_bgp_table_dump_kafka_broker_port},
  {"bgp_table_dump_kafka_topic", cfg_key_nfacctd_bgp_table_dump_kafka_topic},
  {"bgp_table_dump_kafka_topic_rr", cfg_key_nfacctd_bgp_table_dump_kafka_topic_rr},
  {"bgp_table_dump_kafka_partition", cfg_key_nfacctd_bgp_table_dump_kafka_partition},
  {"bmp_daemon", cfg_key_nfacctd_bmp},
  {"bmp_daemon_ip", cfg_key_nfacctd_bmp_ip},
  {"bmp_daemon_port", cfg_key_nfacctd_bmp_port},
  {"bmp_daemon_pipe_size", cfg_key_nfacctd_bmp_pipe_size},
  {"bmp_daemon_max_peers", cfg_key_nfacctd_bmp_max_peers},
  {"bmp_daemon_allow_file", cfg_key_nfacctd_bmp_allow_file},
  {"bmp_daemon_ipprec", cfg_key_nfacctd_bmp_ip_precedence},
  {"bmp_daemon_batch", cfg_key_nfacctd_bmp_batch},
  {"bmp_daemon_batch_interval", cfg_key_nfacctd_bmp_batch_interval},
  {"bmp_daemon_msglog_output", cfg_key_nfacctd_bmp_msglog_output},
  {"bmp_daemon_msglog_file", cfg_key_nfacctd_bmp_msglog_file},
  {"bmp_daemon_msglog_amqp_host", cfg_key_nfacctd_bmp_msglog_amqp_host},
  {"bmp_daemon_msglog_amqp_vhost", cfg_key_nfacctd_bmp_msglog_amqp_vhost},
  {"bmp_daemon_msglog_amqp_user", cfg_key_nfacctd_bmp_msglog_amqp_user},
  {"bmp_daemon_msglog_amqp_passwd", cfg_key_nfacctd_bmp_msglog_amqp_passwd},
  {"bmp_daemon_msglog_amqp_exchange", cfg_key_nfacctd_bmp_msglog_amqp_exchange},
  {"bmp_daemon_msglog_amqp_exchange_type", cfg_key_nfacctd_bmp_msglog_amqp_exchange_type},
  {"bmp_daemon_msglog_amqp_routing_key", cfg_key_nfacctd_bmp_msglog_amqp_routing_key},
  {"bmp_daemon_msglog_amqp_routing_key_rr", cfg_key_nfacctd_bmp_msglog_amqp_routing_key_rr},
  {"bmp_daemon_msglog_amqp_persistent_msg", cfg_key_nfacctd_bmp_msglog_amqp_persistent_msg},
  {"bmp_daemon_msglog_amqp_frame_max", cfg_key_nfacctd_bmp_msglog_amqp_frame_max},
  {"bmp_daemon_msglog_amqp_heartbeat_interval", cfg_key_nfacctd_bmp_msglog_amqp_heartbeat_interval},
  {"bmp_daemon_msglog_amqp_retry", cfg_key_nfacctd_bmp_msglog_amqp_retry},
  {"bmp_daemon_msglog_kafka_broker_host", cfg_key_nfacctd_bmp_msglog_kafka_broker_host},
  {"bmp_daemon_msglog_kafka_broker_port", cfg_key_nfacctd_bmp_msglog_kafka_broker_port},
  {"bmp_daemon_msglog_kafka_topic", cfg_key_nfacctd_bmp_msglog_kafka_topic},
  {"bmp_daemon_msglog_kafka_topic_rr", cfg_key_nfacctd_bmp_msglog_kafka_topic_rr},
  {"bmp_daemon_msglog_kafka_partition", cfg_key_nfacctd_bmp_msglog_kafka_partition},
  {"bmp_daemon_msglog_kafka_retry", cfg_key_nfacctd_bmp_msglog_kafka_retry},
  {"bmp_table_peer_buckets", cfg_key_nfacctd_bmp_table_peer_buckets},
  {"bmp_table_per_peer_buckets", cfg_key_nfacctd_bmp_table_per_peer_buckets},
  {"bmp_table_attr_hash_buckets", cfg_key_nfacctd_bmp_table_attr_hash_buckets},
  {"bmp_table_per_peer_hash", cfg_key_nfacctd_bmp_table_per_peer_hash},
  {"bmp_dump_output", cfg_key_nfacctd_bmp_dump_output},
  {"bmp_dump_file", cfg_key_nfacctd_bmp_dump_file},
  {"bmp_dump_latest_file", cfg_key_nfacctd_bmp_dump_latest_file},
  {"bmp_dump_refresh_time", cfg_key_nfacctd_bmp_dump_refresh_time},
  {"bmp_dump_amqp_host", cfg_key_nfacctd_bmp_dump_amqp_host},
  {"bmp_dump_amqp_vhost", cfg_key_nfacctd_bmp_dump_amqp_vhost},
  {"bmp_dump_amqp_user", cfg_key_nfacctd_bmp_dump_amqp_user},
  {"bmp_dump_amqp_passwd", cfg_key_nfacctd_bmp_dump_amqp_passwd},
  {"bmp_dump_amqp_exchange", cfg_key_nfacctd_bmp_dump_amqp_exchange},
  {"bmp_dump_amqp_exchange_type", cfg_key_nfacctd_bmp_dump_amqp_exchange_type},
  {"bmp_dump_amqp_routing_key", cfg_key_nfacctd_bmp_dump_amqp_routing_key},
  {"bmp_dump_amqp_routing_key_rr", cfg_key_nfacctd_bmp_dump_amqp_routing_key_rr},
  {"bmp_dump_amqp_persistent_msg", cfg_key_nfacctd_bmp_dump_amqp_persistent_msg},
  {"bmp_dump_amqp_frame_max", cfg_key_nfacctd_bmp_dump_amqp_frame_max},
  {"bmp_dump_amqp_heartbeat_interval", cfg_key_nfacctd_bmp_dump_amqp_heartbeat_interval},
  {"bmp_dump_kafka_broker_host", cfg_key_nfacctd_bmp_dump_kafka_broker_host},
  {"bmp_dump_kafka_broker_port", cfg_key_nfacctd_bmp_dump_kafka_broker_port},
  {"bmp_dump_kafka_topic", cfg_key_nfacctd_bmp_dump_kafka_topic},
  {"bmp_dump_kafka_topic_rr", cfg_key_nfacctd_bmp_dump_kafka_topic_rr},
  {"bmp_dump_kafka_partition", cfg_key_nfacctd_bmp_dump_kafka_partition},
  {"flow_to_rd_map", cfg_key_nfacctd_flow_to_rd_map},
  {"isis_daemon", cfg_key_nfacctd_isis},
  {"isis_daemon_ip", cfg_key_nfacctd_isis_ip},
  {"isis_daemon_net", cfg_key_nfacctd_isis_net},
  {"isis_daemon_iface", cfg_key_nfacctd_isis_iface},
  {"isis_daemon_mtu", cfg_key_nfacctd_isis_mtu},
  {"isis_daemon_msglog", cfg_key_nfacctd_isis_msglog},
  {"igp_daemon", cfg_key_nfacctd_isis},
  {"igp_daemon_map", cfg_key_igp_daemon_map},
  {"igp_daemon_map_msglog", cfg_key_igp_daemon_map_msglog},
#if defined WITH_GEOIP
  {"geoip_ipv4_file", cfg_key_geoip_ipv4_file},
#if defined ENABLE_IPV6
  {"geoip_ipv6_file", cfg_key_geoip_ipv6_file},
#endif
#endif
#if defined WITH_GEOIPV2
  {"geoipv2_file", cfg_key_geoipv2_file},
#endif
  {"uacctd_group", cfg_key_uacctd_group},
  {"uacctd_nl_size", cfg_key_uacctd_nl_size},
  {"uacctd_threshold", cfg_key_uacctd_threshold},
  {"tunnel_0", cfg_key_tunnel_0},
  {"pkt_len_distrib_bins", cfg_key_pkt_len_distrib_bins},
  {"tmp_net_own_field", cfg_key_tmp_net_own_field},
  {"", NULL},
};

static struct plugin_type_entry plugin_types_list[] = {
  {PLUGIN_ID_CORE, 	"core", 	NULL},
  {PLUGIN_ID_MEMORY, 	"memory", 	imt_plugin},
  {PLUGIN_ID_PRINT,	"print",	print_plugin},
  {PLUGIN_ID_NFPROBE,	"nfprobe",	nfprobe_plugin},
  {PLUGIN_ID_SFPROBE,	"sfprobe",	sfprobe_plugin},
#ifdef WITH_MYSQL
  {PLUGIN_ID_MYSQL,	"mysql",	mysql_plugin},
#endif
#ifdef WITH_PGSQL
  {PLUGIN_ID_PGSQL,	"pgsql",	pgsql_plugin},
#endif
#ifdef WITH_SQLITE3
  {PLUGIN_ID_SQLITE3,	"sqlite3",	sqlite3_plugin},
#endif
#ifdef WITH_MONGODB
  {PLUGIN_ID_MONGODB,   "mongodb",      mongodb_plugin},
#endif
#ifdef WITH_RABBITMQ
  {PLUGIN_ID_AMQP,	"amqp",		amqp_plugin},
#endif
#ifdef WITH_KAFKA
  {PLUGIN_ID_KAFKA,     "kafka",        kafka_plugin},
#endif
  {PLUGIN_ID_TEE,	"tee",		tee_plugin},
  {PLUGIN_ID_UNKNOWN,	"",		NULL},
};
#endif

#ifdef __NL_C
static struct tunnel_entry tunnel_handlers_list[] = {
  {"gtp", 	gtp_tunnel_func, 	gtp_tunnel_configurator},
  {"", 		NULL,			NULL},
};

#endif
