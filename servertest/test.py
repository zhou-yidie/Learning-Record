import requests
import threading
import time


def send_request(url, request_num):
    try:
        response = requests.get(url)
        if response.status_code == 200:
            print(f"Request successful. Request number: {request_num}")
        else:
            print(f"Request failed with status code: {response.status_code}. Request number: {request_num}")
    except Exception as e:
        print(f"Request failed with error: {e}. Request number: {request_num}")


def main():
    url = "https://profile-counter.glitch.me/zhou-yidie/count.svg"
    num_requests = 10000  # 要发送的请求数量
    threads = []
    for i in range(num_requests):
        time.sleep(1)
        t = threading.Thread(target=send_request, args=(url, i + 1))
        threads.append(t)
        t.start()
    for t in threads:
        t.join()


if __name__ == "__main__":
    main()