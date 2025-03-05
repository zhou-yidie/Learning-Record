#include <event2/event.h>
#include <event2/http.h>
#include <event2/buffer.h>
#include <stdio.h>

// HTTP 请求回调
void http_request_cb(struct evhttp_request *req, void *arg) {
    struct evbuffer *buf = evbuffer_new();
    evbuffer_add_printf(buf, "Hello from libevent!\n");
    evhttp_send_reply(req, HTTP_OK, "OK", buf);
    evbuffer_free(buf);
}

int main() {
    struct event_base *base = event_base_new();
    struct evhttp *http_server = evhttp_new(base);

    // 绑定端口 8080
    evhttp_bind_socket(http_server, "0.0.0.0", 8080);
    evhttp_set_gencb(http_server, http_request_cb, NULL);

    printf("HTTP server started on port 8080...\n");
    event_base_dispatch(base);

    evhttp_free(http_server);
    event_base_free(base);
    return 0;
}
