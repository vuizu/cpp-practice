FROM ubuntu:22.04

WORKDIR /root

RUN echo 'root:123' | chpasswd

RUN apt update && apt install -y ca-certificates

RUN sed -i \
    -e 's#http://archive.ubuntu.com/ubuntu/#https://mirrors.tuna.tsinghua.edu.cn/ubuntu/#' \
    -e 's#http://security.ubuntu.com/ubuntu/#https://mirrors.tuna.tsinghua.edu.cn/ubuntu/#' \
    /etc/apt/sources.list

RUN apt update && apt -y upgrade && apt -y install python3 g++ git bzip2 gnupg2 make xz-utils clangd vim
# pip3 install --break-system-packages -i https://pypi.tuna.tsinghua.edu.cn/simple clingo

COPY spack.yaml .
ENV BASHRC=/root/.bashrc
ENV SPACK_HOME=/opt/spack

RUN git clone -c feature.manyFiles=true https://github.com/spack/spack.git $SPACK_HOME && \
    echo 'export PATH="/opt/spack/bin:$PATH"' >> $BASHRC && \
    echo '. /opt/spack/share/spack/setup-env.sh' >> $BASHRC && \
    . $BASHRC && \
    spack env create hpc spack.yaml && \
    echo 'spacktivate hpc' >> $BASHRC

# 由于是使用了 spack.yaml，故首次需要手动进行 spack install

# 该容器允许远程连接，需要安装 sshd 服务
RUN apt update && apt install -y openssh-server && \
    echo "PermitRootLogin yes" >> /etc/ssh/sshd_config && \
    echo "PubkeyAuthentication yes" >> /etc/ssh/sshd_config && \
    /etc/init.d/ssh restart

# 释放一些空间，减小镜像体积
RUN apt clean && apt autoremove && rm -rf /var/lib/apt/lists/* /tmp/*

# CMD ["tail", "-F", "/dev/null"]
CMD ["/usr/sbin/sshd", "-D"]