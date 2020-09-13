from django.shortcuts import render
from django.http import HttpResponse
from django.views import View


class ViewMenu(View):
    def get(self, request, *args, **kwargs):
        print('!@#$%^: ', request)
        return render(
            request,
            "info_list.html",
            {
                "list": ['code', 'eat', 'sleep', 'repeat'],
            }
        )


class ViewInfo(View):
    def get(self, request):

        page_address = ''
        if 'info_elements/code' in str(request):
            page_address = 'info_elements/code.html'
        elif 'info_elements/eat' in str(request):
            page_address = 'info_elements/eat.html'
        elif 'info_elements/sleep' in str(request):
            page_address = 'info_elements/sleep.html'
        elif 'info_elements/repeat' in str(request):
            page_address = 'info_elements/repeat.html'
        else:
            HttpResponse('Error 404: Not found.')

        print('!@#$%^: ', request)
        return render(
            request,
            page_address,
        )
