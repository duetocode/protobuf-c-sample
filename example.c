#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <message.pb-c.h>

void print_hex(const uint8_t *data, size_t len)
{
    size_t i;
    for (i = 0; i < len; i++)
    {
        printf("%02x", data[i]);
    }
    printf("\n");
}

int main()
{
    const char *body = "Hello, World!";

    // Intialized the message
    Message msg = MESSAGE__INIT;
    msg.serial_number = 1;
    msg.content_type = MESSAGE__CONTENT_TYPE__TEXT_PLAIN;
    msg.payload.data = (uint8_t *)body;
    msg.payload.len = strlen(body);

    // Serialization
    size_t buf_len = message__get_packed_size(&msg);
    uint8_t buf[buf_len];
    message__pack(&msg, buf);

    printf("Serialized length: %zu\n", buf_len);
    print_hex(buf, buf_len);

    // Deserialization
    Message *deserialized = message__unpack(NULL, buf_len, buf);
    printf("\nDeserialized: \n");
    printf("\tSerial number: %d\n", deserialized->serial_number);
    printf("\tContent type: %d(%s)\n",
           deserialized->content_type,
           message__content_type__descriptor.values[deserialized->content_type].name);
    printf("\tPayload: %s\n", (char *)deserialized->payload.data);

    printf("Done.\n");
}