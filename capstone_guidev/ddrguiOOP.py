import tkinter as tk

LARGE_FONT= ("Verdana", 12)

class orthoGUI(tk.Tk):
    def __init__(self, *args, **kwargs):
        tk.Tk.__init__(self, *args, **kwargs)
        container = tk.Frame(self)
        container.pack(side="top", fill="both", expand=True)

        self.frames = {}
        frame1 = MainMenu(container, self)
        frame2 = AvatarSelect(container, self)
        frame3 = GameLoop(container, self)
        self.frames[MainMenu] = frame1
        self.frames[AvatarSelect] = frame2
        self.frames[GameLoop] = frame3
        
        frame1.grid(row=0, column=0, sticky="nsew")
        frame2.grid(row=0, column=0, sticky="nsew")
        frame3.grid(row=0, column=0, sticky="nsew")

        self.show_frame(MainMenu)

        self.title("Ortho-Matryx")
        self.geometry('800x800')

    def show_frame(self, cont):
        frame = self.frames[cont]
        frame.tkraise()

class MainMenu(tk.Frame):
    def __init__(self, parent, controller):
        tk.Frame.__init__(self, parent)
        self.controller = controller

        # replace with GIMP/PhotoShop created title
        titleVar = tk.StringVar()
        titleVar.set("Ortho-Matryx")
        mmTitle = tk.Label(parent, textvariable=titleVar, font="Helvetica", relief=tk.RAISED)

        avatarButton = tk.Button(parent, text = "Select Avatar", command = lambda:self.controller.show_frame(AvatarSelect))
        qpButton = tk.Button(parent, text = "Quick Play", command = lambda:self.controller.show_frame(GameLoop))

        mmTitle.place(relx=0.5, rely = 0.4, anchor = tk.CENTER)
        avatarButton.place(relx=0.5, rely = 0.5, anchor = tk.CENTER)
        qpButton.place(relx=0.5, rely = 0.58, anchor = tk.CENTER)

class AvatarSelect(tk.Frame):
    def __init__(self, parent, controller):
        tk.Frame.__init__(self,parent)
        self.controller = controller

        print("got here")

        returnMM_AS = tk.Button(parent, text = "Return to Main Menu", command = lambda:self.controller.show_frame(MainMenu))
        returnMM_AS.grid(row = 10, column = 1)

class GameLoop(tk.Frame):
    def __init__(self, parent, controller):
        tk.Frame.__init__(self,parent)
        self.controller = controller

        print("got here")

if __name__ == "__main__":
    app = orthoGUI()
    app.mainloop()