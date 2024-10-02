/* DESCRIPTION:
 * This example demonstrates using ESP32-S2/S3/P4 as a USB network device. ,
 * the USB device acts as a standard network interface/ethernet
 */

#include <stdio.h>

#include "esp_log.h"
#include "esp_event.h"
#include "esp_check.h"
#include "nvs_flash.h"

#include "esp_netif.h"
#include "esp_event.h"
#include "esp_http_server.h"

#include "usb_netif.h"

static const char *TAG = "USB_NCM";

static httpd_handle_t s_web_server = NULL;

static esp_err_t http_get_handler(httpd_req_t *req)
{
    const char page[] = "Hello from CDC-NCM ethernet over USB example";
    httpd_resp_set_type(req, "text/html");
    httpd_resp_send(req, page, sizeof(page));
    return ESP_OK;
}

static const httpd_uri_t root = {
    .uri = "/",
    .method = HTTP_GET,
    .handler = http_get_handler,
};

static void start_webserver(void)
{
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    config.max_open_sockets = 7;
    config.lru_purge_enable = true;

    // Start the httpd server
    ESP_LOGI(TAG, "Starting server on port: '%d'", config.server_port);
    if (httpd_start(&s_web_server, &config) == ESP_OK)
    {
        // Set URI handlers
        ESP_LOGI(TAG, "Registering URI handlers");
        httpd_register_uri_handler(s_web_server, &root);
    }
}


void app_main(void)
{
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    ESP_ERROR_CHECK(esp_netif_init());

    usb_ip_init_default_config();
    start_webserver();

    ESP_LOGI(TAG, "USB NCM initialized and started");
    return;
}
