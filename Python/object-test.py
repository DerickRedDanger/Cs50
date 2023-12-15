class Student:
    def __init__(self,name,id):
        self.name = name
        self.id = id

    def changeID(self,id):
        self.id = id

    def print (self):
        print("{} - {}".format(self.name,self.id))

Jane = Student ("Jane", 10)
Jane.print()
Jane.changeID(11)
Jane.print()