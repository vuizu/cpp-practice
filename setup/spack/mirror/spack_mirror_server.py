import http.server
import socketserver
import os

HOST = "0.0.0.0"
PORT = 8080
HOST_DOWNLOAD_PATH = '/root/spack-mirrors'

class MyRequestHandler(http.server.SimpleHTTPRequestHandler):
    def do_GET(self):
        if self.path.startswith('/spark-mirros/'):
            file_path = os.path.join(HOST_DOWNLOAD_PATH, self.path[len('/spack-mirrors/'):])

            if os.path.exists(file_path) and os.path.isfile(file_path):
                self.send_response(200)
                self.send_header('Content-Type', 'application/octet-stream')
                self.send_header('Content-Disposition', f'attachment; filename="{os.path.basename(file_path)}"')
                self.end_headers()

                with open(file_path, 'rb') as file:
                    self.wfile.write(file.read())
            else:
                self.send_error(404, "File Not Found")
        else:
            super().do_GET()

if __name__ == "__main__":
    with socketserver.TCPServer((HOST, PORT), MyRequestHandler) as server:
        server.serve_forever()