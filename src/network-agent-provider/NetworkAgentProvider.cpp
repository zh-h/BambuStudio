#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <boost/format.hpp>
#include <boost/log/trivial.hpp>
#include <rpc/server.h>
#include <string>

#include "../slic3r/Utils/NetworkAgent.hpp"

static std::string g_data_dir;

void set_data_dir(const std::string &dir)
{
    // TODO invoke this
    g_data_dir = dir;
}

const std::string& data_dir()
{
    return g_data_dir;
}

namespace Slic3r {

static void* netwoking_module = NULL;
static void* source_module = NULL;

func_check_debug_consistent         NetworkAgent::check_debug_consistent_ptr = nullptr;
func_get_version                    NetworkAgent::get_version_ptr = nullptr;
func_create_agent                   NetworkAgent::create_agent_ptr = nullptr;
func_destroy_agent                  NetworkAgent::destroy_agent_ptr = nullptr;
func_init_log                       NetworkAgent::init_log_ptr = nullptr;
func_set_config_dir                 NetworkAgent::set_config_dir_ptr = nullptr;
func_set_cert_file                  NetworkAgent::set_cert_file_ptr = nullptr;
func_set_country_code               NetworkAgent::set_country_code_ptr = nullptr;
func_start                          NetworkAgent::start_ptr = nullptr;
func_set_on_ssdp_msg_fn             NetworkAgent::set_on_ssdp_msg_fn_ptr = nullptr;
func_set_on_user_login_fn           NetworkAgent::set_on_user_login_fn_ptr = nullptr;
func_set_on_printer_connected_fn    NetworkAgent::set_on_printer_connected_fn_ptr = nullptr;
func_set_on_server_connected_fn     NetworkAgent::set_on_server_connected_fn_ptr = nullptr;
func_set_on_http_error_fn           NetworkAgent::set_on_http_error_fn_ptr = nullptr;
func_set_get_country_code_fn        NetworkAgent::set_get_country_code_fn_ptr = nullptr;
func_set_on_subscribe_failure_fn    NetworkAgent::set_on_subscribe_failure_fn_ptr = nullptr;
func_set_on_message_fn              NetworkAgent::set_on_message_fn_ptr = nullptr;
func_set_on_user_message_fn         NetworkAgent::set_on_user_message_fn_ptr = nullptr;
func_set_on_local_connect_fn        NetworkAgent::set_on_local_connect_fn_ptr = nullptr;
func_set_on_local_message_fn        NetworkAgent::set_on_local_message_fn_ptr = nullptr;
func_set_queue_on_main_fn           NetworkAgent::set_queue_on_main_fn_ptr = nullptr;
func_connect_server                 NetworkAgent::connect_server_ptr = nullptr;
func_is_server_connected            NetworkAgent::is_server_connected_ptr = nullptr;
func_refresh_connection             NetworkAgent::refresh_connection_ptr = nullptr;
func_start_subscribe                NetworkAgent::start_subscribe_ptr = nullptr;
func_stop_subscribe                 NetworkAgent::stop_subscribe_ptr = nullptr;
func_add_subscribe                  NetworkAgent::add_subscribe_ptr = nullptr;
func_del_subscribe                  NetworkAgent::del_subscribe_ptr = nullptr;
func_enable_multi_machine           NetworkAgent::enable_multi_machine_ptr = nullptr;
func_start_device_subscribe         NetworkAgent::start_device_subscribe_ptr = nullptr;
func_stop_device_subscribe          NetworkAgent::stop_device_subscribe_ptr = nullptr;
func_send_message                   NetworkAgent::send_message_ptr = nullptr;
func_connect_printer                NetworkAgent::connect_printer_ptr = nullptr;
func_disconnect_printer             NetworkAgent::disconnect_printer_ptr = nullptr;
func_send_message_to_printer        NetworkAgent::send_message_to_printer_ptr = nullptr;
func_start_discovery                NetworkAgent::start_discovery_ptr = nullptr;
func_change_user                    NetworkAgent::change_user_ptr = nullptr;
func_is_user_login                  NetworkAgent::is_user_login_ptr = nullptr;
func_user_logout                    NetworkAgent::user_logout_ptr = nullptr;
func_get_user_id                    NetworkAgent::get_user_id_ptr = nullptr;
func_get_user_name                  NetworkAgent::get_user_name_ptr = nullptr;
func_get_user_avatar                NetworkAgent::get_user_avatar_ptr = nullptr;
func_get_user_nickanme              NetworkAgent::get_user_nickanme_ptr = nullptr;
func_build_login_cmd                NetworkAgent::build_login_cmd_ptr = nullptr;
func_build_logout_cmd               NetworkAgent::build_logout_cmd_ptr = nullptr;
func_build_login_info               NetworkAgent::build_login_info_ptr = nullptr;
func_get_model_id_from_desgin_id    NetworkAgent::get_model_id_from_desgin_id_ptr = nullptr;
func_ping_bind                      NetworkAgent::ping_bind_ptr = nullptr;
func_bind_detect                    NetworkAgent::bind_detect_ptr = nullptr;
func_set_server_callback            NetworkAgent::set_server_callback_ptr = nullptr;
func_bind                           NetworkAgent::bind_ptr = nullptr;
func_unbind                         NetworkAgent::unbind_ptr = nullptr;
func_get_bambulab_host              NetworkAgent::get_bambulab_host_ptr = nullptr;
func_get_user_selected_machine      NetworkAgent::get_user_selected_machine_ptr = nullptr;
func_set_user_selected_machine      NetworkAgent::set_user_selected_machine_ptr = nullptr;
func_start_print                    NetworkAgent::start_print_ptr = nullptr;
func_start_local_print_with_record  NetworkAgent::start_local_print_with_record_ptr = nullptr;
func_start_send_gcode_to_sdcard     NetworkAgent::start_send_gcode_to_sdcard_ptr = nullptr;
func_start_local_print              NetworkAgent::start_local_print_ptr = nullptr;
func_start_sdcard_print             NetworkAgent::start_sdcard_print_ptr = nullptr;
func_get_user_presets               NetworkAgent::get_user_presets_ptr = nullptr;
func_request_setting_id             NetworkAgent::request_setting_id_ptr = nullptr;
func_put_setting                    NetworkAgent::put_setting_ptr = nullptr;
func_get_setting_list               NetworkAgent::get_setting_list_ptr = nullptr;
func_get_setting_list2              NetworkAgent::get_setting_list2_ptr = nullptr;
func_delete_setting                 NetworkAgent::delete_setting_ptr = nullptr;
func_get_studio_info_url            NetworkAgent::get_studio_info_url_ptr = nullptr;
func_set_extra_http_header          NetworkAgent::set_extra_http_header_ptr = nullptr;
func_get_my_message                 NetworkAgent::get_my_message_ptr = nullptr;
func_check_user_task_report         NetworkAgent::check_user_task_report_ptr = nullptr;
func_get_user_print_info            NetworkAgent::get_user_print_info_ptr = nullptr;
func_get_user_tasks                 NetworkAgent::get_user_tasks_ptr = nullptr;
func_get_printer_firmware           NetworkAgent::get_printer_firmware_ptr = nullptr;
func_get_task_plate_index           NetworkAgent::get_task_plate_index_ptr = nullptr;
func_get_user_info                  NetworkAgent::get_user_info_ptr = nullptr;
func_request_bind_ticket            NetworkAgent::request_bind_ticket_ptr = nullptr;
func_get_subtask_info               NetworkAgent::get_subtask_info_ptr = nullptr;
func_get_slice_info                 NetworkAgent::get_slice_info_ptr = nullptr;
func_query_bind_status              NetworkAgent::query_bind_status_ptr = nullptr;
func_modify_printer_name            NetworkAgent::modify_printer_name_ptr = nullptr;
func_get_camera_url                 NetworkAgent::get_camera_url_ptr = nullptr;
func_get_design_staffpick           NetworkAgent::get_design_staffpick_ptr = nullptr;
func_start_pubilsh                  NetworkAgent::start_publish_ptr = nullptr;
func_get_profile_3mf                NetworkAgent::get_profile_3mf_ptr = nullptr;
func_get_model_publish_url          NetworkAgent::get_model_publish_url_ptr = nullptr;
func_get_model_mall_home_url        NetworkAgent::get_model_mall_home_url_ptr = nullptr;
func_get_model_mall_detail_url      NetworkAgent::get_model_mall_detail_url_ptr = nullptr;
func_get_subtask                    NetworkAgent::get_subtask_ptr = nullptr;
func_get_my_profile                 NetworkAgent::get_my_profile_ptr = nullptr;
func_track_enable                   NetworkAgent::track_enable_ptr = nullptr;
func_track_remove_files             NetworkAgent::track_remove_files_ptr = nullptr;
func_track_event                    NetworkAgent::track_event_ptr = nullptr;
func_track_header                   NetworkAgent::track_header_ptr = nullptr;
func_track_update_property          NetworkAgent::track_update_property_ptr = nullptr;
func_track_get_property             NetworkAgent::track_get_property_ptr = nullptr;
func_put_model_mall_rating_url      NetworkAgent::put_model_mall_rating_url_ptr = nullptr;
func_get_oss_config                 NetworkAgent::get_oss_config_ptr = nullptr;
func_put_rating_picture_oss         NetworkAgent::put_rating_picture_oss_ptr = nullptr;
func_get_model_mall_rating_result   NetworkAgent::get_model_mall_rating_result_ptr  = nullptr;

func_get_mw_user_preference         NetworkAgent::get_mw_user_preference_ptr = nullptr;
func_get_mw_user_4ulist             NetworkAgent::get_mw_user_4ulist_ptr     = nullptr;

/**
Copy from NetworkAgent.cpp
*/
static func_check_debug_consistent         check_debug_consistent_ptr;
static func_get_version                    get_version_ptr;
static func_create_agent                   create_agent_ptr;
static func_destroy_agent                  destroy_agent_ptr;
static func_init_log                       init_log_ptr;
static func_set_config_dir                 set_config_dir_ptr;
static func_set_cert_file                  set_cert_file_ptr;
static func_set_country_code               set_country_code_ptr;
static func_start                          start_ptr;
static func_set_on_ssdp_msg_fn             set_on_ssdp_msg_fn_ptr;
static func_set_on_user_login_fn           set_on_user_login_fn_ptr;
static func_set_on_printer_connected_fn    set_on_printer_connected_fn_ptr;
static func_set_on_server_connected_fn     set_on_server_connected_fn_ptr;
static func_set_on_http_error_fn           set_on_http_error_fn_ptr;
static func_set_get_country_code_fn        set_get_country_code_fn_ptr;
static func_set_on_subscribe_failure_fn    set_on_subscribe_failure_fn_ptr;
static func_set_on_message_fn              set_on_message_fn_ptr;
static func_set_on_user_message_fn         set_on_user_message_fn_ptr;
static func_set_on_local_connect_fn        set_on_local_connect_fn_ptr;
static func_set_on_local_message_fn        set_on_local_message_fn_ptr;
static func_set_queue_on_main_fn           set_queue_on_main_fn_ptr;
static func_connect_server                 connect_server_ptr;
static func_is_server_connected            is_server_connected_ptr;
static func_refresh_connection             refresh_connection_ptr;
static func_start_subscribe                start_subscribe_ptr;
static func_stop_subscribe                 stop_subscribe_ptr;
static func_add_subscribe                  add_subscribe_ptr;
static func_del_subscribe                  del_subscribe_ptr;
static func_enable_multi_machine           enable_multi_machine_ptr;
static func_start_device_subscribe         start_device_subscribe_ptr;
static func_stop_device_subscribe          stop_device_subscribe_ptr;
static func_send_message                   send_message_ptr;
static func_connect_printer                connect_printer_ptr;
static func_disconnect_printer             disconnect_printer_ptr;
static func_send_message_to_printer        send_message_to_printer_ptr;
static func_start_discovery                start_discovery_ptr;
static func_change_user                    change_user_ptr;
static func_is_user_login                  is_user_login_ptr;
static func_user_logout                    user_logout_ptr;
static func_get_user_id                    get_user_id_ptr;
static func_get_user_name                  get_user_name_ptr;
static func_get_user_avatar                get_user_avatar_ptr;
static func_get_user_nickanme              get_user_nickanme_ptr;
static func_build_login_cmd                build_login_cmd_ptr;
static func_build_logout_cmd               build_logout_cmd_ptr;
static func_build_login_info               build_login_info_ptr;
static func_get_model_id_from_desgin_id    get_model_id_from_desgin_id_ptr;
static func_ping_bind                      ping_bind_ptr;
static func_bind_detect                    bind_detect_ptr;
static func_set_server_callback            set_server_callback_ptr;
static func_bind                           bind_ptr;
static func_unbind                         unbind_ptr;
static func_get_bambulab_host              get_bambulab_host_ptr;
static func_get_user_selected_machine      get_user_selected_machine_ptr;
static func_set_user_selected_machine      set_user_selected_machine_ptr;
static func_start_print                    start_print_ptr;
static func_start_local_print_with_record  start_local_print_with_record_ptr;
static func_start_send_gcode_to_sdcard     start_send_gcode_to_sdcard_ptr;
static func_start_local_print              start_local_print_ptr;
static func_start_sdcard_print             start_sdcard_print_ptr;
static func_get_user_presets               get_user_presets_ptr;
static func_request_setting_id             request_setting_id_ptr;
static func_put_setting                    put_setting_ptr;
static func_get_setting_list               get_setting_list_ptr;
static func_get_setting_list2              get_setting_list2_ptr;
static func_delete_setting                 delete_setting_ptr;
static func_get_studio_info_url            get_studio_info_url_ptr;
static func_set_extra_http_header          set_extra_http_header_ptr;
static func_get_my_message                 get_my_message_ptr;
static func_check_user_task_report         check_user_task_report_ptr;
static func_get_user_print_info            get_user_print_info_ptr;
static func_get_user_tasks                 get_user_tasks_ptr;
static func_get_printer_firmware           get_printer_firmware_ptr;
static func_get_task_plate_index           get_task_plate_index_ptr;
static func_get_user_info                  get_user_info_ptr;
static func_request_bind_ticket            request_bind_ticket_ptr;
static func_get_subtask_info               get_subtask_info_ptr;
static func_get_slice_info                 get_slice_info_ptr;
static func_query_bind_status              query_bind_status_ptr;
static func_modify_printer_name            modify_printer_name_ptr;
static func_get_camera_url                 get_camera_url_ptr;
static func_get_design_staffpick           get_design_staffpick_ptr;
static func_start_pubilsh                  start_publish_ptr;
static func_get_profile_3mf                get_profile_3mf_ptr;
static func_get_model_publish_url          get_model_publish_url_ptr;
static func_get_subtask                    get_subtask_ptr;
static func_get_model_mall_home_url        get_model_mall_home_url_ptr;
static func_get_model_mall_detail_url      get_model_mall_detail_url_ptr;
static func_get_my_profile                 get_my_profile_ptr;
static func_track_enable                   track_enable_ptr;
static func_track_remove_files             track_remove_files_ptr;
static func_track_event                    track_event_ptr;
static func_track_header                   track_header_ptr;
static func_track_update_property          track_update_property_ptr;
static func_track_get_property             track_get_property_ptr;
static func_put_model_mall_rating_url      put_model_mall_rating_url_ptr;
static func_get_oss_config                 get_oss_config_ptr;
static func_put_rating_picture_oss         put_rating_picture_oss_ptr;
static func_get_model_mall_rating_result   get_model_mall_rating_result_ptr;

static func_get_mw_user_preference get_mw_user_preference_ptr;
static func_get_mw_user_4ulist     get_mw_user_4ulist_ptr;


void* get_network_function(const char* name)
{
    void* function = nullptr;

    if (!netwoking_module)
        return function;
    function = dlsym(netwoking_module, name);

    if (!function) {
        BOOST_LOG_TRIVIAL(warning) << __FUNCTION__ << boost::format(", can not find function %1%")%name;
    }
    return function;
}

int initialize_network_module(bool using_backup)
{
    //int ret = -1;
    std::string library;
    std::string data_dir_str = data_dir();
    boost::filesystem::path data_dir_path(data_dir_str);
    auto plugin_folder = data_dir_path / "plugins";

    if (using_backup) {
        plugin_folder = plugin_folder/"backup";
    }

    //first load the library
    library = plugin_folder.string() + "/" + std::string("lib") + std::string(BAMBU_NETWORK_LIBRARY) + ".so";
    printf("loading network module at %s\n", library.c_str());
    netwoking_module = dlopen( library.c_str(), RTLD_LAZY);
    if (!netwoking_module) {
        /*#if defined(__WXMAC__)
        library = std::string("lib") + BAMBU_NETWORK_LIBRARY + ".dylib";
        #else
        library = std::string("lib") + BAMBU_NETWORK_LIBRARY + ".so";
        #endif*/
        //netwoking_module = dlopen( library.c_str(), RTLD_LAZY);
        char* dll_error = dlerror();
        printf("error, dlerror is %s\n", dll_error);
        BOOST_LOG_TRIVIAL(info) << __FUNCTION__ << boost::format(", error, dlerror is %1%")%dll_error;
    }
    printf("after dlopen, network_module is %p\n", netwoking_module);

    if (!netwoking_module) {
        BOOST_LOG_TRIVIAL(info) << __FUNCTION__ << boost::format(", can not Load Library for %1%")%library;
        return -1;
    }
    BOOST_LOG_TRIVIAL(info) << __FUNCTION__ << boost::format(", successfully loaded library %1%, module %2%")%library %netwoking_module;

    //load the functions
    check_debug_consistent_ptr        =  reinterpret_cast<func_check_debug_consistent>(get_network_function("bambu_network_check_debug_consistent"));
    get_version_ptr                   =  reinterpret_cast<func_get_version>(get_network_function("bambu_network_get_version"));
    create_agent_ptr                  =  reinterpret_cast<func_create_agent>(get_network_function("bambu_network_create_agent"));
    destroy_agent_ptr                 =  reinterpret_cast<func_destroy_agent>(get_network_function("bambu_network_destroy_agent"));
    init_log_ptr                      =  reinterpret_cast<func_init_log>(get_network_function("bambu_network_init_log"));
    set_config_dir_ptr                =  reinterpret_cast<func_set_config_dir>(get_network_function("bambu_network_set_config_dir"));
    set_cert_file_ptr                 =  reinterpret_cast<func_set_cert_file>(get_network_function("bambu_network_set_cert_file"));
    set_country_code_ptr              =  reinterpret_cast<func_set_country_code>(get_network_function("bambu_network_set_country_code"));
    start_ptr                         =  reinterpret_cast<func_start>(get_network_function("bambu_network_start"));
    set_on_ssdp_msg_fn_ptr            =  reinterpret_cast<func_set_on_ssdp_msg_fn>(get_network_function("bambu_network_set_on_ssdp_msg_fn"));
    set_on_user_login_fn_ptr          =  reinterpret_cast<func_set_on_user_login_fn>(get_network_function("bambu_network_set_on_user_login_fn"));
    set_on_printer_connected_fn_ptr   =  reinterpret_cast<func_set_on_printer_connected_fn>(get_network_function("bambu_network_set_on_printer_connected_fn"));
    set_on_server_connected_fn_ptr    =  reinterpret_cast<func_set_on_server_connected_fn>(get_network_function("bambu_network_set_on_server_connected_fn"));
    set_on_http_error_fn_ptr          =  reinterpret_cast<func_set_on_http_error_fn>(get_network_function("bambu_network_set_on_http_error_fn"));
    set_get_country_code_fn_ptr       =  reinterpret_cast<func_set_get_country_code_fn>(get_network_function("bambu_network_set_get_country_code_fn"));
    set_on_subscribe_failure_fn_ptr   =  reinterpret_cast<func_set_on_subscribe_failure_fn>(get_network_function("bambu_network_set_on_subscribe_failure_fn"));
    set_on_message_fn_ptr             =  reinterpret_cast<func_set_on_message_fn>(get_network_function("bambu_network_set_on_message_fn"));
    set_on_user_message_fn_ptr        =  reinterpret_cast<func_set_on_user_message_fn>(get_network_function("bambu_network_set_on_user_message_fn"));
    set_on_local_connect_fn_ptr       =  reinterpret_cast<func_set_on_local_connect_fn>(get_network_function("bambu_network_set_on_local_connect_fn"));
    set_on_local_message_fn_ptr       =  reinterpret_cast<func_set_on_local_message_fn>(get_network_function("bambu_network_set_on_local_message_fn"));
    set_queue_on_main_fn_ptr          = reinterpret_cast<func_set_queue_on_main_fn>(get_network_function("bambu_network_set_queue_on_main_fn"));
    connect_server_ptr                =  reinterpret_cast<func_connect_server>(get_network_function("bambu_network_connect_server"));
    is_server_connected_ptr           =  reinterpret_cast<func_is_server_connected>(get_network_function("bambu_network_is_server_connected"));
    refresh_connection_ptr            =  reinterpret_cast<func_refresh_connection>(get_network_function("bambu_network_refresh_connection"));
    start_subscribe_ptr               =  reinterpret_cast<func_start_subscribe>(get_network_function("bambu_network_start_subscribe"));
    stop_subscribe_ptr                =  reinterpret_cast<func_stop_subscribe>(get_network_function("bambu_network_stop_subscribe"));
    add_subscribe_ptr                 =  reinterpret_cast<func_add_subscribe>(get_network_function("bambu_network_add_subscribe"));
    del_subscribe_ptr                 =  reinterpret_cast<func_del_subscribe>(get_network_function("bambu_network_del_subscribe"));
    enable_multi_machine_ptr          =  reinterpret_cast<func_enable_multi_machine>(get_network_function("bambu_network_enable_multi_machine"));
    start_device_subscribe_ptr        =  reinterpret_cast<func_start_device_subscribe>(get_network_function("bambu_network_start_device_subscribe"));
    stop_device_subscribe_ptr         =  reinterpret_cast<func_stop_device_subscribe>(get_network_function("bambu_network_stop_device_subscribe"));
    send_message_ptr                  =  reinterpret_cast<func_send_message>(get_network_function("bambu_network_send_message"));
    connect_printer_ptr               =  reinterpret_cast<func_connect_printer>(get_network_function("bambu_network_connect_printer"));
    disconnect_printer_ptr            =  reinterpret_cast<func_disconnect_printer>(get_network_function("bambu_network_disconnect_printer"));
    send_message_to_printer_ptr       =  reinterpret_cast<func_send_message_to_printer>(get_network_function("bambu_network_send_message_to_printer"));
    start_discovery_ptr               =  reinterpret_cast<func_start_discovery>(get_network_function("bambu_network_start_discovery"));
    change_user_ptr                   =  reinterpret_cast<func_change_user>(get_network_function("bambu_network_change_user"));
    is_user_login_ptr                 =  reinterpret_cast<func_is_user_login>(get_network_function("bambu_network_is_user_login"));
    user_logout_ptr                   =  reinterpret_cast<func_user_logout>(get_network_function("bambu_network_user_logout"));
    get_user_id_ptr                   =  reinterpret_cast<func_get_user_id>(get_network_function("bambu_network_get_user_id"));
    get_user_name_ptr                 =  reinterpret_cast<func_get_user_name>(get_network_function("bambu_network_get_user_name"));
    get_user_avatar_ptr               =  reinterpret_cast<func_get_user_avatar>(get_network_function("bambu_network_get_user_avatar"));
    get_user_nickanme_ptr             =  reinterpret_cast<func_get_user_nickanme>(get_network_function("bambu_network_get_user_nickanme"));
    build_login_cmd_ptr               =  reinterpret_cast<func_build_login_cmd>(get_network_function("bambu_network_build_login_cmd"));
    build_logout_cmd_ptr              =  reinterpret_cast<func_build_logout_cmd>(get_network_function("bambu_network_build_logout_cmd"));
    build_login_info_ptr              =  reinterpret_cast<func_build_login_info>(get_network_function("bambu_network_build_login_info"));
    ping_bind_ptr                     =  reinterpret_cast<func_ping_bind>(get_network_function("bambu_network_ping_bind"));
    bind_detect_ptr                   =  reinterpret_cast<func_bind_detect>(get_network_function("bambu_network_bind_detect"));
    set_server_callback_ptr           =  reinterpret_cast<func_set_server_callback>(get_network_function("bambu_network_set_server_callback"));
    get_model_id_from_desgin_id_ptr   =  reinterpret_cast<func_get_model_id_from_desgin_id>(get_network_function("bambu_network_get_model_id_from_desgin_id"));
    bind_ptr                          =  reinterpret_cast<func_bind>(get_network_function("bambu_network_bind"));
    unbind_ptr                        =  reinterpret_cast<func_unbind>(get_network_function("bambu_network_unbind"));
    get_bambulab_host_ptr             =  reinterpret_cast<func_get_bambulab_host>(get_network_function("bambu_network_get_bambulab_host"));
    get_user_selected_machine_ptr     =  reinterpret_cast<func_get_user_selected_machine>(get_network_function("bambu_network_get_user_selected_machine"));
    set_user_selected_machine_ptr     =  reinterpret_cast<func_set_user_selected_machine>(get_network_function("bambu_network_set_user_selected_machine"));
    start_print_ptr                   =  reinterpret_cast<func_start_print>(get_network_function("bambu_network_start_print"));
    start_local_print_with_record_ptr =  reinterpret_cast<func_start_local_print_with_record>(get_network_function("bambu_network_start_local_print_with_record"));
    start_send_gcode_to_sdcard_ptr    =  reinterpret_cast<func_start_send_gcode_to_sdcard>(get_network_function("bambu_network_start_send_gcode_to_sdcard"));
    start_local_print_ptr             =  reinterpret_cast<func_start_local_print>(get_network_function("bambu_network_start_local_print"));
    start_sdcard_print_ptr            =  reinterpret_cast<func_start_sdcard_print>(get_network_function("bambu_network_start_sdcard_print"));
    get_user_presets_ptr              =  reinterpret_cast<func_get_user_presets>(get_network_function("bambu_network_get_user_presets"));
    request_setting_id_ptr            =  reinterpret_cast<func_request_setting_id>(get_network_function("bambu_network_request_setting_id"));
    put_setting_ptr                   =  reinterpret_cast<func_put_setting>(get_network_function("bambu_network_put_setting"));
    get_setting_list_ptr              = reinterpret_cast<func_get_setting_list>(get_network_function("bambu_network_get_setting_list"));
    get_setting_list2_ptr             = reinterpret_cast<func_get_setting_list2>(get_network_function("bambu_network_get_setting_list2"));
    delete_setting_ptr                =  reinterpret_cast<func_delete_setting>(get_network_function("bambu_network_delete_setting"));
    get_studio_info_url_ptr           =  reinterpret_cast<func_get_studio_info_url>(get_network_function("bambu_network_get_studio_info_url"));
    set_extra_http_header_ptr         =  reinterpret_cast<func_set_extra_http_header>(get_network_function("bambu_network_set_extra_http_header"));
    get_my_message_ptr                =  reinterpret_cast<func_get_my_message>(get_network_function("bambu_network_get_my_message"));
    check_user_task_report_ptr        =  reinterpret_cast<func_check_user_task_report>(get_network_function("bambu_network_check_user_task_report"));
    get_user_print_info_ptr           =  reinterpret_cast<func_get_user_print_info>(get_network_function("bambu_network_get_user_print_info"));
    get_user_tasks_ptr                =  reinterpret_cast<func_get_user_tasks>(get_network_function("bambu_network_get_user_tasks"));
    get_printer_firmware_ptr          =  reinterpret_cast<func_get_printer_firmware>(get_network_function("bambu_network_get_printer_firmware"));
    get_task_plate_index_ptr          =  reinterpret_cast<func_get_task_plate_index>(get_network_function("bambu_network_get_task_plate_index"));
    get_user_info_ptr                 =  reinterpret_cast<func_get_user_info>(get_network_function("bambu_network_get_user_info"));
    request_bind_ticket_ptr           =  reinterpret_cast<func_request_bind_ticket>(get_network_function("bambu_network_request_bind_ticket"));
    get_subtask_info_ptr              =  reinterpret_cast<func_get_subtask_info>(get_network_function("bambu_network_get_subtask_info"));
    get_slice_info_ptr                =  reinterpret_cast<func_get_slice_info>(get_network_function("bambu_network_get_slice_info"));
    query_bind_status_ptr             =  reinterpret_cast<func_query_bind_status>(get_network_function("bambu_network_query_bind_status"));
    modify_printer_name_ptr           =  reinterpret_cast<func_modify_printer_name>(get_network_function("bambu_network_modify_printer_name"));
    get_camera_url_ptr                =  reinterpret_cast<func_get_camera_url>(get_network_function("bambu_network_get_camera_url"));
    get_design_staffpick_ptr          =  reinterpret_cast<func_get_design_staffpick>(get_network_function("bambu_network_get_design_staffpick"));
    start_publish_ptr                 =  reinterpret_cast<func_start_pubilsh>(get_network_function("bambu_network_start_publish"));
    get_profile_3mf_ptr               =  reinterpret_cast<func_get_profile_3mf>(get_network_function("bambu_network_get_profile_3mf"));
    get_model_publish_url_ptr         =  reinterpret_cast<func_get_model_publish_url>(get_network_function("bambu_network_get_model_publish_url"));
    get_subtask_ptr                   =  reinterpret_cast<func_get_subtask>(get_network_function("bambu_network_get_subtask"));
    get_model_mall_home_url_ptr       =  reinterpret_cast<func_get_model_mall_home_url>(get_network_function("bambu_network_get_model_mall_home_url"));
    get_model_mall_detail_url_ptr     =  reinterpret_cast<func_get_model_mall_detail_url>(get_network_function("bambu_network_get_model_mall_detail_url"));
    get_my_profile_ptr                =  reinterpret_cast<func_get_my_profile>(get_network_function("bambu_network_get_my_profile"));
    track_enable_ptr                  =  reinterpret_cast<func_track_enable>(get_network_function("bambu_network_track_enable"));
    track_remove_files_ptr            =  reinterpret_cast<func_track_remove_files>(get_network_function("bambu_network_track_remove_files"));
    track_event_ptr                   =  reinterpret_cast<func_track_event>(get_network_function("bambu_network_track_event"));
    track_header_ptr                  =  reinterpret_cast<func_track_header>(get_network_function("bambu_network_track_header"));
    track_update_property_ptr         = reinterpret_cast<func_track_update_property>(get_network_function("bambu_network_track_update_property"));
    track_get_property_ptr            = reinterpret_cast<func_track_get_property>(get_network_function("bambu_network_track_get_property"));
    put_model_mall_rating_url_ptr     = reinterpret_cast<func_put_model_mall_rating_url>(get_network_function("bambu_network_put_model_mall_rating"));
    get_oss_config_ptr                = reinterpret_cast<func_get_oss_config>(get_network_function("bambu_network_get_oss_config"));
    put_rating_picture_oss_ptr        = reinterpret_cast<func_put_rating_picture_oss>(get_network_function("bambu_network_put_rating_picture_oss"));
    get_model_mall_rating_result_ptr  = reinterpret_cast<func_get_model_mall_rating_result>(get_network_function("bambu_network_get_model_mall_rating"));

    get_mw_user_preference_ptr = reinterpret_cast<func_get_mw_user_preference>(get_network_function("bambu_network_get_mw_user_preference"));
    get_mw_user_4ulist_ptr     = reinterpret_cast<func_get_mw_user_4ulist>(get_network_function("bambu_network_get_mw_user_4ulist"));

    return 0;
}

int unload_network_module()
{
    BOOST_LOG_TRIVIAL(info) << __FUNCTION__ << boost::format(", network module %1%")%netwoking_module;
    if (netwoking_module) {
        dlclose(netwoking_module);
        netwoking_module = NULL;
    }
    if (source_module) {
        dlclose(source_module);
        source_module = NULL;
    }

    check_debug_consistent_ptr        =  nullptr;
    get_version_ptr                   =  nullptr;
    create_agent_ptr                  =  nullptr;
    destroy_agent_ptr                 =  nullptr;
    init_log_ptr                      =  nullptr;
    set_config_dir_ptr                =  nullptr;
    set_cert_file_ptr                 =  nullptr;
    set_country_code_ptr              =  nullptr;
    start_ptr                         =  nullptr;
    set_on_ssdp_msg_fn_ptr            =  nullptr;
    set_on_user_login_fn_ptr          =  nullptr;
    set_on_printer_connected_fn_ptr   =  nullptr;
    set_on_server_connected_fn_ptr    =  nullptr;
    set_on_http_error_fn_ptr          =  nullptr;
    set_get_country_code_fn_ptr       =  nullptr;
    set_on_subscribe_failure_fn_ptr   =  nullptr;
    set_on_message_fn_ptr             =  nullptr;
    set_on_user_message_fn_ptr        =  nullptr;
    set_on_local_connect_fn_ptr       =  nullptr;
    set_on_local_message_fn_ptr       =  nullptr;
    set_queue_on_main_fn_ptr          = nullptr;
    connect_server_ptr                =  nullptr;
    is_server_connected_ptr           =  nullptr;
    refresh_connection_ptr            =  nullptr;
    start_subscribe_ptr               =  nullptr;
    stop_subscribe_ptr                =  nullptr;
    send_message_ptr                  =  nullptr;
    connect_printer_ptr               =  nullptr;
    disconnect_printer_ptr            =  nullptr;
    send_message_to_printer_ptr       =  nullptr;
    start_discovery_ptr               =  nullptr;
    change_user_ptr                   =  nullptr;
    is_user_login_ptr                 =  nullptr;
    user_logout_ptr                   =  nullptr;
    get_user_id_ptr                   =  nullptr;
    get_user_name_ptr                 =  nullptr;
    get_user_avatar_ptr               =  nullptr;
    get_user_nickanme_ptr             =  nullptr;
    build_login_cmd_ptr               =  nullptr;
    build_logout_cmd_ptr              =  nullptr;
    build_login_info_ptr              =  nullptr;
    get_model_id_from_desgin_id_ptr   =  nullptr;
    ping_bind_ptr                     =  nullptr;
    bind_ptr                          =  nullptr;
    unbind_ptr                        =  nullptr;
    get_bambulab_host_ptr             =  nullptr;
    get_user_selected_machine_ptr     =  nullptr;
    set_user_selected_machine_ptr     =  nullptr;
    start_print_ptr                   =  nullptr;
    start_local_print_with_record_ptr =  nullptr;
    start_send_gcode_to_sdcard_ptr    =  nullptr;
    start_local_print_ptr             =  nullptr;
    start_sdcard_print_ptr             =  nullptr;
    get_user_presets_ptr              =  nullptr;
    request_setting_id_ptr            =  nullptr;
    put_setting_ptr                   =  nullptr;
    get_setting_list_ptr              =  nullptr;
    get_setting_list2_ptr             =  nullptr;
    delete_setting_ptr                =  nullptr;
    get_studio_info_url_ptr           =  nullptr;
    set_extra_http_header_ptr         =  nullptr;
    get_my_message_ptr                =  nullptr;
    check_user_task_report_ptr        =  nullptr;
    get_user_print_info_ptr           =  nullptr;
    get_user_tasks_ptr                =  nullptr;
    get_printer_firmware_ptr          =  nullptr;
    get_task_plate_index_ptr          =  nullptr;
    get_user_info_ptr                 =  nullptr;
    get_subtask_info_ptr              =  nullptr;
    get_slice_info_ptr                =  nullptr;
    query_bind_status_ptr             =  nullptr;
    modify_printer_name_ptr           =  nullptr;
    get_camera_url_ptr                =  nullptr;
    get_design_staffpick_ptr          =  nullptr;
    start_publish_ptr                 =  nullptr;
    get_profile_3mf_ptr               =  nullptr;
    get_model_publish_url_ptr         =  nullptr;
    get_subtask_ptr                   =  nullptr;
    get_model_mall_home_url_ptr       =  nullptr;
    get_model_mall_detail_url_ptr     =  nullptr;
    get_my_profile_ptr                =  nullptr;
    track_enable_ptr                  =  nullptr;
    track_remove_files_ptr            =  nullptr;
    track_event_ptr                   =  nullptr;
    track_header_ptr                  =  nullptr;
    track_update_property_ptr         =  nullptr;
    track_get_property_ptr            =  nullptr;
    get_oss_config_ptr                =  nullptr;
    put_rating_picture_oss_ptr        =  nullptr;
    put_model_mall_rating_url_ptr     =  nullptr;
    get_model_mall_rating_result_ptr  = nullptr;

    get_mw_user_preference_ptr        = nullptr;
    get_mw_user_4ulist_ptr            = nullptr;

    return 0;
}
}

void test() {
    BOOST_LOG_TRIVIAL(info) << __FUNCTION__ << boost::format(", hello");
    Slic3r::initialize_network_module(false);
    rpc::server srv(8081);
    srv.bind("get_version_ptr", Slic3r::get_version_ptr);
    srv.bind("check_debug_consistent_ptr", Slic3r::check_debug_consistent_ptr);
    BOOST_LOG_TRIVIAL(info) << __FUNCTION__ << boost::format(", function registed");
    srv.run();
}

int main() {
    set_data_dir(std::string(std::getenv("HOME")) + "/.config/BambuStudioInternal");
    test();
    return 0;
}