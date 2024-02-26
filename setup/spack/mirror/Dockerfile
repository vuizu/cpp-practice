FROM alpine:latest
WORKDIR /root
RUN sed -i 's/dl-cdn.alpinelinux.org/mirrors.aliyun.com/g' /etc/apk/repositories
RUN apk add --update --no-cache tzdata python3
ENV TZ=Asia/Shanghai

COPY spack_mirror_server.py .

CMD ["python3", "spack_mirror_server.py"]

# docker build -t upload -f ./Dockerfile .
# docker run -d \
#            --name upload-container \
#            -p 8080:8080 \
#            -v ~/spack-mirror:/root/spack-mirror \
#            upload
# spack container：spack mirror add remote_url http://172.12.0.2:8080/spack-mirrors