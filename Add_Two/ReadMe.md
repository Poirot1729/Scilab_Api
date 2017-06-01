# Usage
```scilab
files=['path_to_addsum.cpp'];
WITHOUT_AUTO_PUTLHSVAR=%t;
ilib_build('addsum',['add','add_sum'],files,[]);
exec loader.sce
[ans]=add(2,3)
```
