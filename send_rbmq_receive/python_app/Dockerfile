FROM python:3.8

RUN pip install pika


COPY app.py /app/app.py
WORKDIR /app
CMD ["tail", "-f", "/dev/null"]

# CMD ["python3", "app.py"]