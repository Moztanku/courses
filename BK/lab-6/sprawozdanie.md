# Sprawozdanie

### Certyfikat ze strony cs.pwr.edu.pl

```
-----BEGIN CERTIFICATE-----
MIIFYzCCBEugAwIBAgISA+HiQNImdtE7y1VU9pwEU2MiMA0GCSqGSIb3DQEBCwUA
... stuff ...
ThKjpl5XKvw/0xCNmohKsssxOv+lve6gS7mMobL9nDiAocSJalCj
-----END CERTIFICATE-----
-----BEGIN CERTIFICATE-----
MIIFFjCCAv6gAwIBAgIRAJErCErPDBinU/bWLiWnX1owDQYJKoZIhvcNAQELBQAw
... stuff ...
nLRbwHOoq7hHwg==
-----END CERTIFICATE-----
-----BEGIN CERTIFICATE-----
MIIFazCCA1OgAwIBAgIRAIIQz7DSQONZRGPgu2OCiwAwDQYJKoZIhvcNAQELBQAw
... stuff ...
emyPxgcYxn/eR44/KJ4EBs+lVDR3veyJm+kXQ99b21/+jh5Xos1AnX5iItreGCc=
-----END CERTIFICATE-----

```

### Używanie openssl x509 do analizy certyfikatu

#### Sprawdzenie kto podpisał certyfikat

```console
$ openssl x509 -in cert.pem -noout -issuer
issuer= /C=US/O=Let's Encrypt/CN=R3
```

#### Jaki jest algorytm podpisu?

```console
$ openssl x509 -in cert.pem -noout -text | grep "Signature Algorithm"
        Signature Algorithm: sha256WithRSAEncryption
    Signature Algorithm: sha256WithRSAEncryption
```

#### Jaka jest data ważności certyfikatu?

```console
$ openssl x509 -in cert.pem -noout -dates
notBefore=Jun  1 07:11:40 2024 GMT
notAfter=Aug 30 07:11:39 2024 GMT
```

#### Dla kogo jest certyfikat?

```console
$ openssl x509 -in cert.pem -noout -subject
subject=CN=cs.pwr.edu.pl
```

#### Jakie domeny obejmuje?

```console
$ openssl x509 -in cert.pem -noout -text | grep "DNS"
                DNS:cs.pwr.edu.pl, DNS:ifipsec2018.pwr.edu.pl, DNS:ki.pwr.edu.pl, DNS:knsi.pwr.wroc.pl, DNS:settheory.pwr.edu.pl, DNS:studia.cs.pwr.edu.pl, DNS:www.knsi.pwr.wroc.pl
```

#### Jakie rozszerzenia x509 są użyte?

```console
$ openssl x509 -in cert.pem -noout -text | grep "X509v3"
        X509v3 extensions:
            X509v3 Key Usage: critical
            X509v3 Extended Key Usage: 
            X509v3 Basic Constraints: critical
            X509v3 Subject Key Identifier: 
            X509v3 Authority Key Identifier: 
            X509v3 Subject Alternative Name: 
            X509v3 Certificate Policies:
```

#### Jakie jest URI do list CRL i URI do OCSP?

```console
$ openssl x509 -in cert.pem -noout -ocsp_uri
http://r3.o.lencr.org
$ openssl x509 -in cert.pem -noout -text | grep "CRL"
# In this case there is no CRL URI
```

#### Używając polecenia openssl verify, sprawdź czy certyfikat jest poprawny

```console
$ openssl verify -CAfile cert.pem cs-pwr-edu-pl.pem
cs-pwr-edu-pl.pem: OK
```

#### Używając polecenia openssl ocsp i znalezionego adresu OCSP, sprawdź czy certyfikat jest poprawny

```console
$ openssl ocsp -issuer r3.pem -cert cs-pwr-edu-pl.pem -url http://r3.o.lencr.org
WARNING: no nonce in response
Response verify OK
cs-pwr-edu-pl.pem: good
        This Update: Jun 15 21:46:00 2024 GMT
        Next Update: Jun 22 21:45:58 2024 GMT
```

#### Wykorzystaj OpenSSL do wygenerowanie pary kluczy Prywatny/Publiczny

```console
$ openssl genrsa -out private.pem 2048
$ openssl rsa -in private.pem -outform PEM -pubout -out public.pem
```

#### Wygeneruj żądanie certyfikatu CSR

```console
$ openssl req -new -key private.pem -out csr.pem
```

#### Korzystając z Certbota wygeneruj certyfikat

```console
# First we need to install certbot
$ sudo pacman -S certbot certbot-nginx
# Then we can generate the certificate
$ sudo certbot certonly --nginx
```
