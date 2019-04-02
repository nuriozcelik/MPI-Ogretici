#### BROADCAST ÖRNEĞİ
###### !!Önceden açıklamaları yapılan bazı fonksiyonlar açıklanmayacaktır!!

```sh
    MPI_Reduce(&buffer, &reception, buffer_count, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD); 
```

**Amacı :** Tüm işlemlerde bulunan verileri tek veriye indirger.

**Makrosu :** int MPI_Reduce(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, int root, MPI_Comm comm)

**Çıktı Parametreleri :** 

recvbuf -> alma bufferının adresi (sadece kök islemde son veriye erisilir)

**Girdi Parametreleri :** 

sendbuf -> gönderim bufferının adresi 

count -> Buffer içerisinde bulunan eleman sayısı (integer)

datatype -> bufferın veri tipi 

op -> indirgeme işlem seçimi 

root -> veri paylaşılan process in ID si(rank) (integer)

comm -> communicator


!! tekrar hatırlatayım root veri gönderen processin kimliğidir.



İyi çalışmalar




