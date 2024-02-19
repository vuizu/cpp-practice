import copy
import torch

"""
python -m venv .venv -> 创建 virtual environment
在WSL的Ubuntu中，需要先使用apt install python3.10-venv


安装pytorch命令: 
    pip3 install torch torchvision torchaudio --index-url https://download.pytorch.org/whl/cu121 
                                             windows上不能指定清华源，否则下载的是 cpu版本 -i https://pypi.tuna.tsinghua.edu.cn/simple

检查cuda是否安装
    import torch
    print(torch.cuda.is_available())

"""

if __name__ == "__main__":
    # 数据类型转换
    '''
    数据类型转换
    '''
    # int()   # int('3.14') wrong -> int(float('3.14')) right
    # float()
    # complex()
    # str()
    # list()  # [1, 2, 3]
    # set()   # {1, 2, 3}
    # tuple() # (1, 2, 3)
    # dict()  # {'name': 'Peter', 'age': 18}
    st = 'Hello World1'
    fun = lambda a: a + 1
    x, y, z = 1, 2, 3

    # enumerate会在遍历时加上索引
    for idx, ch in enumerate('Hello World'):
        print(f'idx: {idx}, ch: {ch}')
    print(st[-1])


    s = "yes" if not st else "no"
    
    print(torch.cuda.is_available())


def code_style() -> None:
    # todo 1. 不要通过长度判断容器或序列是否为空
    ls = []
    # if len(ls) == 0: 不正确
    if not ls:  # 判断为空
        pass
    elif ls:  # 判断有内容
        pass

    # todo 2. 把否定词直接写在要否定的内容前面
    a, b = 1, 2
    if a is not b:  # if not a is b: 不正确
        pass


class Father:
    def __init__(self):
        self.__private_data = None
        self._protected_data = None


class ListStatics(Father):
    # 一个下划线开头，受保护的实例属性
    # 两个下划线开头，私有的实例属性
    # 实例方法第一个参数命名为self
    # 类方法第一个参数命名为cls
    # 静态方法不需要指定特定参数
    def __init__(self, data=None):
        super().__init__()
        if data is None:
            data = []
        self.__data = data

    @property
    def set_data(self):
        return self.__data

    @set_data.setter
    def set_data(self, new_list):
        if self._are_all_numeric(new_list):
            self.__data = new_list
        else:
            pass

    @classmethod
    def _are_all_numeric(cls, input_list: list) -> bool:
        for elem in input_list:
            if not isinstance(elem, (int, float)):
                return False
        return True

    @staticmethod
    def _say():
        pass


obj = ListStatics()
obj.set_data = [1.1, 2, '3.3']