FROM asilla/product_core:v2.6.0


RUN apt update && apt install -y  librabbitmq-dev

COPY . /app
WORKDIR /app


RUN g++ -o cpp_app main.cpp -lrabbitmq

CMD ["tail", "-f", "/dev/null"]

# CMD ["./send_message"]