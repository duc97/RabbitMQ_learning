import pika
import time
import json

def callback(ch, method, properties, body):
    data = json.loads(body)
    # with open("data.json", "w") as file:
    #     json.dump(data, file, indent=4)
    # print(f" [x] Received {body.decode()}")
    print(f" [x] Received {data}")
    print("\n--------------------------------\n\n")

def main():
    while True:
        try:
            credentials = pika.PlainCredentials('user', 'password')
            parameters = pika.ConnectionParameters(
                host='192.168.30.132',
                port=5672,        
                credentials=credentials
            )
            connection = pika.BlockingConnection(parameters)
            channel = connection.channel()
            channel.queue_declare(queue='test_queue', durable=True)
            channel.basic_consume(
                queue='test_queue', on_message_callback=callback, auto_ack=True
            )
            print(" [*] Waiting for messages. To exit press CTRL+C")
            channel.start_consuming()

        except pika.exceptions.AMQPConnectionError:
            print(" [!] Connection failed. Retrying in 5 seconds...")
            time.sleep(5)

if __name__ == "__main__":
    main()