import os
import subprocess


# setup 目录的位置
setup_path = os.path.abspath(os.path.dirname(__file__))

def root_exec(cmd):
    # passwd ==> '123'
    os.system(f"echo '123' | sudo -S {cmd}")

# subprocess.DEVNULL
def exec(cmd, shell=True, check=True, stderr=None, stdout=None):
    subprocess.run(cmd, shell=shell, check=check, stderr=stderr, stdout=stdout)

###################################################################################################
def host_apt_source():
    exec("""
        sudo sed -i 's#http://archive.ubuntu.com/ubuntu/#https://mirrors.tuna.tsinghua.edu.cn/ubuntu/#' /etc/apt/sources.list &&
        sudo sed -i 's#http://security.ubuntu.com/ubuntu/#https://mirrors.tuna.tsinghua.edu.cn/ubuntu/#' /etc/apt/sources.list
        """)

def host_docker():
    host_apt_source()
    exec("""
        sudo apt update && sudo apt install -y ca-certificates curl && sudo install -m 0755 -d /etc/apt/keyrings && \
            sudo curl -fsSL https://download.docker.com/linux/ubuntu/gpg -o /etc/apt/keyrings/docker.asc && \
                sudo chmod a+r /etc/apt/keyrings/docker.asc
            """)
    exec("""
        echo \
            "deb [arch=$(dpkg --print-architecture) signed-by=/etc/apt/keyrings/docker.asc] https://download.docker.com/linux/ubuntu \
            $(. /etc/os-release && echo "$VERSION_CODENAME") stable" | \
            sudo tee /etc/apt/sources.list.d/docker.list > /dev/null && \
                sudo apt update
            """)
    exec("""
        sudo apt install -y docker-ce docker-ce-cli containerd.io docker-buildx-plugin && \
            sudo usermod -aG docker $USER
        """) 
    exec("""
         sudo tee /etc/docker/daemon.json <<-'EOF'
         {
            "registry-mirrors": [
                "https://registry.docker-cn.com",
                "https://docker.mirrors.ustc.edu.cn",
                "https://hub-mirror.c.163.com"
            ],
            "exec-opts": [
                "native.cgroupdriver=systemd"
            ],
            "log-driver": "json-file",
            "log-opts": {
                "max-size": "100m"
            },
            "storage-driver": "overlay2"
        }
        EOF
         """)
    exec("sudo systemctl enable docker --now")


def host_nvidia_container_toolkit():
    exec("""
         curl -fsSL https://nvidia.github.io/libnvidia-container/gpgkey | sudo gpg --dearmor -o /usr/share/keyrings/nvidia-container-toolkit-keyring.gpg && \
             curl -s -L https://nvidia.github.io/libnvidia-container/stable/deb/nvidia-container-toolkit.list | \
             sed 's#deb https://#deb [signed-by=/usr/share/keyrings/nvidia-container-toolkit-keyring.gpg] https://#g' | \
             sudo tee /etc/apt/sources.list.d/nvidia-container-toolkit.list
         """)
    exec("sudo apt update && sudo apt install -y nvidia-container-toolkit")
    exec("sudo nvidia-ctk runtime configure --runtime=docker && sudo systemctl restart docker")
    

###################################################################################################
def container_spack():
    spack_local_path = f"{setup_path}/spack"
    exec(f"docker build -t spack:latest -f {spack_local_path}/Dockerfile {spack_local_path}")
    exec("""
         docker run \
                 -d \
                 --gpus all \
                 --runtime=nvidia \
                 --name spack_container \
                 -p 8022:22 \
                 -v /home/ntwd/cpp-practice:/root/cpp-practice \
                 spack
         """)
    exec("docker exec -it spack_container /bin/bash")
    

if __name__ == "__main__":
    """
    只用于Ubuntu系统
    需要确保当前用户在sudoer里面
    sudo vim /etc/sudoers => user   ALL=(ALL) NOPASSWD: ALL
    """
    # host_docker()
    # wsl2_nvidia_container_toolkit()
    # container_spack()
