#include "driver/gpio.h"
#include "driver/i2c_master.h"
#include "esp_err.h"

namespace initializer
{

constexpr gpio_num_t QWIIC_SDA_GPIO =
    static_cast<gpio_num_t>(CONFIG_QWIIC_I2C_SDA_GPIO);
constexpr gpio_num_t QWIIC_SCL_GPIO =
    static_cast<gpio_num_t>(CONFIG_QWIIC_I2C_SCL_GPIO);

i2c_master_bus_handle_t qwiic_bus = nullptr;

void qwiic_i2c_init()
{
    i2c_master_bus_config_t bus_config = {};
    bus_config.i2c_port = I2C_NUM_0;
    bus_config.sda_io_num = QWIIC_SDA_GPIO;
    bus_config.scl_io_num = QWIIC_SCL_GPIO;
    bus_config.clk_source = I2C_CLK_SRC_DEFAULT;
    bus_config.glitch_ignore_cnt = 7;
    bus_config.flags.enable_internal_pullup = true;

    ESP_ERROR_CHECK(i2c_new_master_bus(&bus_config, &qwiic_bus));
}

} // namespace

extern "C" void app_main(void)
{
    initializer::qwiic_i2c_init();
}
