
#include <stm32f10x_conf.h>
#include "device.hpp"
#include "timex.hpp"
#include "stdio.h"
#include <oled.h>

using namespace dev;

#include "os.h"









int main(void) {
    usart io = usart(1, 9600);

    os_init(2, new gpio('C', 13));

    delay_ms(20);

    oled show = oled(iicx(gpio('A', 1), gpio('A', 2)));

    show.clear();
    show.print(1, 0, "test");

    time htim = time(3);

    htim.setCallback(gpio::toggle, new gpio('A', 0));
    htim.period(50); // 10k    50us
    htim.period(5);  // 100k

    while (true) {
        while (!os_execult());
    }
}