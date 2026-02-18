TinyML Dinamik Tensör Yönetimi Projesi
Bu çalışma, bellek kapasitesi oldukça kısıtlı olan mikrodenetleyiciler (Arduino, ESP32, STM32 vb.) üzerinde yapay zeka modellerini verimli bir şekilde çalıştırabilmek amacıyla geliştirilmiş özel bir veri yönetim sistemidir. Bir Gömülü Sistem Mühendisi perspektifiyle hazırlanan bu proje, "Quantization" (Nicemleme) tekniklerini kullanarak RAM kullanımını optimize etmeyi hedefler.

Projenin Temel Mantığı
Standart bilgisayarlarda kullanılan 32-bit kayan noktalı sayılar (float), küçük cihazların belleğini çok çabuk tüketir. Bu projede tasarlanan dinamik tensör yapısı, veriyi ihtiyaca göre farklı hassasiyet seviyelerinde saklayabilir. Sistem; yüksek hassasiyet gerektiren durumlarda tam kapasite çalışırken, bellek kritik seviyeye geldiğinde veriyi otomatik olarak daha az yer kaplayan formatlara dönüştürür.

Teknik Özellikler ve Kazanımlar
Esnek Veri Yapısı: Aynı veri alanı içinde Float32 (4 Byte), Float16 (2 Byte) veya Int8 (1 Byte) veriler saklanabilir.

Bellek Verimliliği: Int8 dönüşümü sayesinde başlangıçtaki bellek ihtiyacı yüzde 75 oranında azaltılır.

Akıllı Optimizasyon (Agentic Yaklaşım): Kod, sadece statik bir depolama alanı değil, aynı zamanda verinin boyutunu ve sistemin kısıtlarını analiz ederek en uygun veri tipine karar veren bir mekanizmaya sahiptir.

Dinamik Ölçekleme: Veriler sıkıştırılırken bilgi kaybını minimize etmek için en büyük değer baz alınarak dinamik bir ölçekleme katsayısı (Scale) hesaplanır.

Kullanılan Mühendislik Yöntemleri
Proje geliştirilirken C programlama dilinin en güçlü yönlerinden olan "Union" yapısı tercih edilmiştir. Bu sayede farklı veri tipleri bellekte aynı adresi paylaşarak gereksiz yer işgalini önler. Ayrıca dinamik bellek yönetimi (malloc/free) sayesinde, cihaz çalışırken bellek sızıntılarının önüne geçilerek sistem kararlılığı korunur.

Uygulama Senaryosu
Örnek uygulamada, bir sensörden gelen yüksek hassasiyetli veriler önce Float32 formatında sisteme alınır. Sistem, "Agentic" karar mekanizmasını çalıştırarak bu verilerin bellek üzerindeki yükünü analiz eder ve ardından veriyi hassasiyetten ödün vermeden güvenli bir şekilde Int8 formatına sıkıştırarak saklar.
