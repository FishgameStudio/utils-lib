# Documentation of `requests::RESULT`

Class usage: Encapsulates a response from `requests::get`.

```cpp
class RESULT {
private:
    int status_code;
    std::string html;
public:
    RESULT(int status_code, std::string html);
    int get_status_code() const;
    const std::string get_html() const;
};
```

**Purpose**: Store the HTTP status code and response body returned by `requests::get`.


# Documentation of function `requests::get`

Function usage: Send a simple HTTP GET request to the specified URL and return the parsed result.

Implementation:
```cpp
RESULT get(const std::string& url);
```

**Behavior**:
- Supports `http://` URLs and plain host/path URLs.
- Uses port `80` and HTTP/1.0 only.
- Resolves the host via DNS, opens a TCP socket, sends the request, and reads the full response.
- Parses the response header to extract the HTTP status code and body.

**Return**: `requests::RESULT` containing:
- `status_code` — HTTP response status code.
- `html` — response body.

**Example**:
```cpp
requests::RESULT res = requests::get("http://example.com/index.html");
int status = res.get_status_code();
std::string body = res.get_html();
```

**Exceptions**:
- `std::runtime_error("Failed to initialize Winsock")`
- `std::runtime_error("Only HTTP protocol is supported")`
- `std::runtime_error("Failed to create socket")`
- `std::runtime_error("Failed to resolve host")`
- `std::runtime_error("Failed to connect to server")`
- `std::runtime_error("Failed to send request")`
- `std::runtime_error("Failed to receive response")`
- `std::runtime_error("Invalid response")`

**Notes**:
- HTTPS is not supported.
- The function reads the response until the socket closes.
- The body returned by `get_html()` excludes the HTTP response headers.
