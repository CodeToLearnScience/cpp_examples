
#include <algorithm>
#include <deque>
#include <iostream>
#include <optional>
#include <stdio.h>

class URL {

public:
  URL(const std::string &protocol, const std::string &resources)
      : protocol(protocol), resources(resources) {}

  void display() { std::cout << protocol << "://" << resources << "\n"; }

  std::string get_url() { return protocol + "://" + resources; }
  std::string get_url() const { return protocol + "://" + resources; }

  friend bool operator==(const URL &url1, const URL &url2);

private:
  std::string protocol;
  std::string resources;
};

bool operator==(const URL &url1, const URL &url2) {
  return url1.get_url() == url2.get_url();
}

class URLs {
public:
  URLs() = default;
  URLs(const URL &url) : _url(url) { urls.push_front(url); }

  void add_url(const URL &url) {
    if (!urls.empty()) {
      auto found = std::find(urls.begin(), urls.end(), url);
      if (found != urls.end()) {
        auto temp = *found;
        urls.erase(found);
        urls.push_front(temp);
      } else {
        urls.push_front(url);
      }
    } else {
      urls.push_front(url);
    }
  }

  void display_urls() {
    for (auto url : urls) {
      std::cout << url.get_url() << "\n";
    }
  }

private:
  std::optional<URL> _url;
  std::deque<URL> urls;
};

int main() {

  URL url("https", "www.google.com");
  URL url2("https", "www.yahoo.com");
  URL url3("https", "www.ms.com");

  URLs urls(url);
  urls.add_url(url);
  urls.add_url(url2);
  urls.add_url(url3);
  urls.add_url(url2);

  urls.display_urls();

  URLs urls1;
  URL url4("https", "www.mit.com");
  urls1.add_url(url4);
  urls1.display_urls();
  return 0;
}
