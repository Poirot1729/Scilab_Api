# Usage
```scilab
files=['path_to_addsum.cpp'];
WITHOUT_AUTO_PUTLHSVAR=%t;
ilib_build('addsum',['add','add_sum'],files,[]);
exec loader.sce
[ans]=add(2,3)
```
## Output
![selection_009](https://cloud.githubusercontent.com/assets/15849927/26693561/3b52f188-4722-11e7-9963-abf252c03edf.png)

