| Freq (Hz) | Period (ms) | p99 (µs) | p999 (µs) | Max (µs) |
|-----------|-------------|----------|-----------|----------|
| 250       | 4.0         | 836      | 1562      | 55012    |
| 500       | 2.0         | 433      | 815       | 3594     |
| 750       | 1.33333     | 362      | 715       | 51814    |   
| 1000      | 1.0         | 300      | 407       | 1964     |
| 2000      | 0.5         | 246      | 468       | 1175     |
| 4000      | 0.25        | 179      | 435       | 2584     |



p99 ve p999, bir sistemin ortalama değil, en kötü anlara ne kadar dayanıklı olduğunu gösterir. p99, ölçümlerin %99’unun altında kaldığı gecikmeyi; p999 ise her 1000 ölçümde bir yaşanan çok nadir ama kritik gecikmeyi temsil eder. 
Gerçek-zamanlı (RT) sistemlerde deadline’ı kaçıran şey genellikle bu nadir olaylardır;bu yüzden kararlar p99/p999 üzerinden verilir, ortalama değerler güven verici olsa bile belirleyici değildir.

Max, ölçülen en büyük gecikmedir ve genellikle scheduler, interrupt, power-state geçişleri gibi tekil ve kontrolü zor olayları yansıtır. Bu nedenle Max, sistemin “başına gelebilecek en kötü şey”i gösterir ama tasarım kararı için ana metrik değildir.
RT pratikte p99/p999 ile güvenli iş bütçesi belirlenir; Max ise yalnızca outlier var mı? sorusuna cevap verir.

# Örnek

En kritik deadline **audio** sistemlerindedir. Herhangi bir bug'ın telafisi yoktur ve tüm işler titizlikle hesaplanmalıdır.

Burada audio terminolojisine dikkat ederek iki temel formülü verebiliriz. Bu sayede, audio sistemleri için de bir motor yazılabilir. 

Sesin, 48 kHz'te örneklendiğini düşünelim, burada hesaplamamız gereken parametre callback frekansıdır.
Tick rate, audio için örnekleme frekansı değildir.Buffer olarak alır ve bu buffer'ın her seferinde doldurulması gerekir.
Buffer boyutunu 64 olarak düşünürsek, bir örneği baştan sona alabilmemiz için buffer'ın boyutunu her bir örneğin süresi 
ile çarpmamız gerekir. Bu da bize aslında bir audio örneğinin hiçbir parçası kaçmadan sığabileceği zamanı verir:

Fcb=sample_rate/buffer_size
Tdeadline=buffer_size/sample_rate

64 sample → 750 Hz → 1.333 ms

1.333 - 0.715 = 0.6 ms

DSP'nin toplam 0.5 ms süresi var, geçtiğinde audio bug'ları yaşanacaktır.
