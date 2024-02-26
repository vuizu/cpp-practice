FROM ubuntu:22.04

WORKDIR /root

RUN apt update && apt install -y ca-certificates

RUN sed -i \
    -e 's#http://archive.ubuntu.com/ubuntu/#https://mirrors.tuna.tsinghua.edu.cn/ubuntu/#' \
    -e 's#http://security.ubuntu.com/ubuntu/#https://mirrors.tuna.tsinghua.edu.cn/ubuntu/#' \
    /etc/apt/sources.list

RUN apt update && apt -y upgrade && apt -y install python3 g++ git bzip2 gnupg2 make xz-utils clangd
# pip3 install --break-system-packages -i https://pypi.tuna.tsinghua.edu.cn/simple clingo

ENV BASHRC=/root/.bashrc
COPY spack.yaml .
RUN git clone -c feature.manyFiles=true https://github.com/spack/spack.git && \
    echo 'export PATH="/root/spack/bin:$PATH"' >> $BASHRC && \
    echo '. /root/spack/share/spack/setup-env.sh' >> $BASHRC && \
    . $BASHRC && \
    spack env create hpc spack.yaml && \
    echo 'spacktivate hpc' >> $BASHRC

# 由于是使用了 spack.yaml，故首次需要手动进行 spack install

# 释放一些空间，减小镜像体积
RUN apt clean && apt autoremove && rm -rf /var/lib/apt/lists/* /tmp/*

CMD ["tail", "-F", "/dev/null"]
