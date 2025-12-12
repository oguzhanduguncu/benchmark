Freq    Period(ms)    p99(us)     p999(us)      Max(us)     
------------------------------------------------------------
250     4             836         1562          55012  
500     2             433         815           3594        
1000    1             300         407           1964     
2000    0.5           246         468           1175        
4000    0.25          179         435           2584        


p99 ve p999, bir sistemin ortalama değil, en kötü anlara ne kadar dayanıklı olduğunu gösterir. p99, ölçümlerin %99’unun altında kaldığı gecikmeyi; p999 ise her 1000 ölçümde bir yaşanan çok nadir ama kritik gecikmeyi temsil eder. 
Gerçek-zamanlı (RT) sistemlerde deadline’ı kaçıran şey genellikle bu nadir olaylardır;bu yüzden kararlar p99/p999 üzerinden verilir, ortalama değerler güven verici olsa bile belirleyici değildir.

Max, ölçülen en büyük gecikmedir ve genellikle scheduler, interrupt, power-state geçişleri gibi tekil ve kontrolü zor olayları yansıtır. Bu nedenle Max, sistemin “başına gelebilecek en kötü şey”i gösterir ama tasarım kararı için ana metrik değildir.
RT pratikte p99/p999 ile güvenli iş bütçesi belirlenir; Max ise yalnızca outlier var mı? sorusuna cevap verir.
