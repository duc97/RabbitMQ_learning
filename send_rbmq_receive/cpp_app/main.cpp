#include <amqp.h>
#include <amqp_tcp_socket.h>
#include <iostream>
#include <string>
#include "json.hpp"
#include <chrono>

void send_message(const std::string &message) {
    auto start = std::chrono::high_resolution_clock::now();
    amqp_connection_state_t conn = amqp_new_connection();
    amqp_socket_t *socket = amqp_tcp_socket_new(conn);

    if (amqp_socket_open(socket, "192.168.30.132", 5672)) {
        std::cerr << "Unable to open socket\n";
        return;
    }

    amqp_login(conn, "/", 0, 131072, 0, AMQP_SASL_METHOD_PLAIN, "user", "password");
    amqp_channel_open(conn, 1);
    amqp_get_rpc_reply(conn);

    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << "connect time: " << duration << " ms\n";

    // amqp_bytes_t queue_name = amqp_cstring_bytes("test_queue");
    // amqp_queue_declare(conn, 1, queue_name, 0, 1, 0, 0, amqp_empty_table);
    // amqp_get_rpc_reply(conn);
    // if (!amqp_frames_enqueued(conn)) {
    //     std::cerr << "No frames available or connection issue1." << std::endl;
    // }
    std::string exchange = "my_exchange";
    std::string routing_key = "my_key"; 
    amqp_bytes_t message_bytes = amqp_cstring_bytes(message.c_str());
    int publish_status = amqp_basic_publish(conn, 1, amqp_cstring_bytes(exchange.c_str()), amqp_cstring_bytes(routing_key.c_str()), 0, 0, NULL, message_bytes);
    if (publish_status != AMQP_STATUS_OK) {
        std::cerr << " [!] Failed to send message: "
                  << amqp_error_string2(publish_status) << std::endl;
    }
    else{
        std::cout << "Message sent ok: " << message << "--" << publish_status << "\n";
    }
    

    std::cout << "Message sent: " << message << "--" << publish_status << "\n";

    amqp_channel_close(conn, 1, AMQP_REPLY_SUCCESS);
    amqp_connection_close(conn, AMQP_REPLY_SUCCESS);
    amqp_destroy_connection(conn);
}

int main() {
    using json = nlohmann::json;
    json json_message = {
        {"name", "Alice"},
        {"age", 30},
        {"city", "Wonderland"}
    };
    std::string json_string = json_message.dump();
    for (int i = 0 ; i < 50; i++){
        send_message(json_string);
    }
    return 0;
}