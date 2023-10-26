#prova creazione app per android
from kivymd.app import MDApp 
from kivy.lang import Builder


KV = """ 
Screen:

    GridLayout:
        rows: 4

    MDLabel:
        id: mdlab
        text: "Controlla i tuoi IP"
        font_style: "H3"

    MDRaisedButton:
        id:mdbu1
        text: "Aggiungi"
        size_hint_x: 1
        pos_hint: {"center_x": 0.5, "center_y": 0.2}
        on_press: app.add_button()

    MDRaisedButton:
        id:mdbu2
        text: "Modifica"
        size_hint_x: 1
        pos_hint: {"center_x": 0.5, "center_y": 0.10}
        #on_press: app.add_button()
"""


class Guardian(MDApp):

    def build(self):
        self.titile = "GuardianIP"
        self.theme_cls.theme_style = "Dark" 
        self.theme_cls.primary_palette = "Green"
        self.theme_cls.primary_hue = "400"
        return Builder.load_string(KV)

    def add_button(self):
        self.root.ids["mdlab"].text = "Funzione di aggiunta attiva"

       
Guardian().run()
