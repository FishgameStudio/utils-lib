# Test **accessibilities** of some websites.
# You can apply this script in your awesome projects to 
# check the accessibility of the URLs in your awesome list.
import requests as req
import urllib3

def test_acessibility(urls: list[str]) -> list[bool]:
    """Test **accessibilities** of some websites."""
    
    # Disable warnings.
    urllib3.disable_warnings(urllib3.exceptions.InsecureRequestWarning)

    result = []
    for url in urls:
        full_url: str
        if not url.startswith("https://"): 
            full_url = f"https://{url}"
        else:
            full_url = url
        
        code: int
        is_ok: bool
        try:
            code = req.get(full_url, verify=False, timeout=5).status_code
            # The code starts with 2xx: ok
            is_ok = code >= 200 and code < 300
        except:
            is_ok = False
        
        result.append(is_ok)
    return result


# Test
if __name__ == '__main__':
    websites = [
        "github.com", 
        "microsoft.com", 
        "example.com", 
        "apple.com"
    ]
    res = test_acessibility(websites)
    print(res)
