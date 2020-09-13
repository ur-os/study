from django.db import models

# Create your models here.


class User(models.Model):
    name = models.CharField(max_length=255)
    number = models.CharField(max_length=255)
    mail = models.CharField(max_length=255)
    img = models.ImageField()

    def __str__(self):
        return self.name


class Order(models.Model):
    application_date = models.DateTimeField()
    shipping_date = models.DateTimeField()
    user_id = models.ForeignKey(User, on_delete=models.CASCADE)


class Notebook(models.Model):
    name = models.CharField(max_length=255)
    cpu = models.CharField(max_length=255)
    gpu = models.CharField(max_length=255)
    mem = models.CharField(max_length=255)
    drive = models.CharField(max_length=255)
    display = models.CharField(max_length=255)
    amount = models.IntegerField()
    price = models.FloatField()

    def __str__(self):
        return self.name


class OrderProduct(models.Model):
    order_id = models.ForeignKey(Order, on_delete=models.CASCADE)
    product_id = models.ForeignKey(Notebook, on_delete=models.CASCADE)
