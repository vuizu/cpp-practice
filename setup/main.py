import os
import subprocess


# setup 目录的位置
setup_path = os.path.abspath(os.path.dirname(__file__))


def root_exec(cmd):
    # passwd ==> '123'
    os.system(f"echo '123' | sudo -S {cmd}")

def exec(cmd):
    subprocess.call(cmd, shell=True, check=True)

"""
先配置 wsl 环境
"""
def wsl2_apt_source():
    cmd = """
        sudo sed -i 's#http://archive.ubuntu.com/ubuntu/#https://mirrors.tuna.tsinghua.edu.cn/ubuntu/#' /etc/apt/sources.list &&
        sudo sed -i 's#http://security.ubuntu.com/ubuntu/#https://mirrors.tuna.tsinghua.edu.cn/ubuntu/#' /etc/apt/sources.list
        """
    exec(cmd)

def wsl2_docker():
    pass

def wsl2_nvidia_container_toolkit():
    exec("""
         curl -fsSL https://nvidia.github.io/libnvidia-container/gpgkey | sudo gpg --dearmor -o /usr/share/keyrings/nvidia-container-toolkit-keyring.gpg \
            && curl -s -L https://nvidia.github.io/libnvidia-container/stable/deb/nvidia-container-toolkit.list | \
                sed 's#deb https://#deb [signed-by=/usr/share/keyrings/nvidia-container-toolkit-keyring.gpg] https://#g' | \
            sudo tee /etc/apt/sources.list.d/nvidia-container-toolkit.list
         """)
    exec("sudo apt update && sudo apt install -y nvidia-container-toolkit")
    


def container_spack():
    """
    规定安装在 /root/spack 下
    docker build -t spack:latest -f Dockerfile .
    
    docker run 
            -d \
            -gpus all \
            --runtime=nvidia \
            --name spack_container \
            -v $setup_path/.spack:$root_path/.spack \
            -v /home/ntwd/cpp-practice:/root/cpp-practice \
            spack

    """
    spack_path = f"{setup_path}/spack"
    exec(f"docker build -t spack:latest -f {spack_path}/Dockerfile {spack_path}")


if __name__ == "__main__":
    wsl2_nvidia_container_toolkit()
    # container_spack()
