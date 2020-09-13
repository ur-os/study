from django.shortcuts import render
from django.http import HttpResponse
from django.views import View
from crackers import forms

class HomePage(View):
    def get(self, request, *args, **kwargs):
        print('!@#$%^: ', request)
        return render(
            request,
            "home.html",
            {

            }
        )


class Registration(View):
    def get(self, request):
        return render(
            request,
            'registration.html',
            {

            }
        )

    def post(self, request):
        return render(
            request,
            'home.html',
            {

            }
        )


class Auth(View):

    def get(self, request, *args, **kwargs):
        print('!@#$%^: ', request)
        return render(
            request,
            "base.html",
            {
                "list": ['code', 'eat', 'sleep', 'repeat'],
            }
        )

    def post(self, request, *args, **kwargs):
        if request.method == 'POST':
            form = RegistrationForm(request.POST)
            if form.is_valid():
                # успех... создание модели пользователя

                return HttpResponseRedirect('/login/')
        else:
            form = RegistrationForm()

        return render(request, 'registration.html', {'form': form})

    def post(self, request):

        errors = []
        if request.method == 'POST':
            username = request.POST.get('username')
            if not username:
                errors.append('Введите логин')
            elif len(username) < 5:
                errors.append('Логин должен привышать 5 символов')

            password = request.POST.get('password')
            if not password:
                errors.append('Введите пароль')
            elif len(password) < 6:
                errors.append('Длинна пароля должна превышать 6 символов')
            password_repeat = request.POST.get('password2')

            if password != password_repeat:
                errors.append('Пароли должны совпадать')

            if not errors:
                # успех... создание модели пользователя

                return HttpResponse('okay')

        return render(request, 'auth.html', {'errors': errors})




class Profile(View):
    pass


class Reg(View):
    pass


class EntityList(View):
    pass


class EntityAdd(View):
    pass


class Entity(View):
    pass