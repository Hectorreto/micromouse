#include <WiFi.h>

const char* ssid = "Totalplay-4DA5";
const char* password = "4DA567C94mSmYq2h";

WiFiServer server(80);
WiFiClient client;
int cnt = 0;

void handleApiRequest() {
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  if (request.startsWith("GET / ")) {
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println(""); // Important: blank line separates headers from body
    client.println(
      R"####(<!DOCTYPE html><html lang="en"> <head><meta charset="UTF-8"><meta name="description" content="Astro description"><meta name="viewport" content="width=device-width"><link rel="icon" type="image/svg+xml" href="/favicon.svg"><meta name="generator" content="Astro v4.8.2"><title>Welcome to Astro.</title><style>:root{--accent: 136, 58, 234;--accent-light: 224, 204, 250;--accent-dark: 49, 10, 101;--accent-gradient: linear-gradient( 45deg, rgb(var(--accent)), rgb(var(--accent-light)) 30%, white 60% )}html{font-family:system-ui,sans-serif;background:#13151a;background-size:224px}code{font-family:Menlo,Monaco,Lucida Console,Liberation Mono,DejaVu Sans Mono,Bitstream Vera Sans Mono,Courier New,monospace}body{font-family:Arial,sans-serif;background-color:#f0f0f0;margin:0;padding:0;display:flex;justify-content:center;align-items:center;height:100vh}.container[data-astro-cid-dohjnao5]{text-align:center;background-color:#fff;border-radius:8px;padding:20px;box-shadow:0 0 10px #0000001a}h1[data-astro-cid-dohjnao5]{font-size:32px;margin-bottom:20px}button[data-astro-cid-dohjnao5]{padding:10px 20px;font-size:16px;cursor:pointer;border:none;border-radius:4px;margin:0 5px;transition:background-color .3s}button[data-astro-cid-dohjnao5]#increment{background-color:#007bff;color:#fff}button[data-astro-cid-dohjnao5]#decrement{background-color:#dc3545;color:#fff}button[data-astro-cid-dohjnao5]:hover{filter:brightness(1.2)}#counter[data-astro-cid-dohjnao5]{font-size:24px;font-weight:700}.container[data-astro-cid-j7pv25f6]{background-color:#f0f0f0;font-family:Arial,Helvetica,sans-serif}</style><script type="module">const e=document.getElementById("counter");let n=Number(e?.innerText||0);const t=document.getElementById("increment");t&&e&&t.addEventListener("click",()=>{e.innerHTML=String(++n),fetch("/api/increment",{method:"POST"}).catch(()=>{e.innerHTML=String(--n)})});const c=document.getElementById("decrement");c&&e&&c.addEventListener("click",()=>{e.innerHTML=String(--n),fetch("/api/decrement",{method:"POST"}).catch(()=>{e.innerHTML=String(++n)})});</script></head> <body>  <main class="container" data-astro-cid-j7pv25f6>  <div class="container" data-astro-cid-dohjnao5> <h1 data-astro-cid-dohjnao5>Hello, World!</h1> <p data-astro-cid-dohjnao5>This is a basic example of HTML.</p> <p data-astro-cid-dohjnao5>Current value of cnt: <span id="counter" data-astro-cid-dohjnao5>)####"
      + String(cnt) +
      R"####(</span></p> <div data-astro-cid-dohjnao5> <button id="increment" type="button" data-astro-cid-dohjnao5>+</button> <button id="decrement" type="button" data-astro-cid-dohjnao5>-</button> </div> </div>  </main>  </body></html>)####"
    );
  } else if (request.startsWith("GET /favicon.svg ")) {
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: image/svg+xml");
    client.println(""); // Important: blank line separates headers from body
    client.println(
      R"(<svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 128 128"><path d="M50.4 78.5a75.1 75.1 0 0 0-28.5 6.9l24.2-65.7c.7-2 1.9-3.2 3.4-3.2h29c1.5 0 2.7 1.2 3.4 3.2l24.2 65.7s-11.6-7-28.5-7L67 45.5c-.4-1.7-1.6-2.8-2.9-2.8-1.3 0-2.5 1.1-2.9 2.7L50.4 78.5Zm-1.1 28.2Zm-4.2-20.2c-2 6.6-.6 15.8 4.2 20.2a17.5 17.5 0 0 1 .2-.7 5.5 5.5 0 0 1 5.7-4.5c2.8.1 4.3 1.5 4.7 4.7.2 1.1.2 2.3.2 3.5v.4c0 2.7.7 5.2 2.2 7.4a13 13 0 0 0 5.7 4.9v-.3l-.2-.3c-1.8-5.6-.5-9.5 4.4-12.8l1.5-1a73 73 0 0 0 3.2-2.2 16 16 0 0 0 6.8-11.4c.3-2 .1-4-.6-6l-.8.6-1.6 1a37 37 0 0 1-22.4 2.7c-5-.7-9.7-2-13.2-6.2Z" /><style>path { fill: #000; }@media (prefers-color-scheme: dark) {path { fill: #FFF; }}</style></svg>)"
    );
  } else if (request.startsWith("POST /api/increment ")) {
    cnt++;
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println(""); // Important: blank line separates headers from body
    client.print("Counter incremented to ");
    client.println(cnt);
  } else if (request.startsWith("POST /api/decrement ")) {
    cnt--;
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println(""); // Important: blank line separates headers from body
    client.print("Counter decremented to ");
    client.println(cnt);
  } else {
    // Return a response for other requests
    client.println("HTTP/1.1 404 Not Found");
    client.println("Content-Type: text/html");
    client.println(""); // Important: blank line separates headers from body
    client.println("<h1>Not Found</h1>");
  }
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Start the server
  server.begin();
}

void loop() {
  // Check if a client has connected
  client = server.available();
  if (client && client.available()) {
    handleApiRequest();
    return;
  }

  delay(100);
}
