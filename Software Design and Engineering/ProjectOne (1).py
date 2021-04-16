from pymongo import MongoClient
from bson.objectid import ObjectId


class AnimalShelter(object):
    """CRUD operations for Animal collection in MongoDB"""
    
    def __init__(self, username, password):
        #initializing the MongoClient. This helps to access the MongoDB databases and collections
        self.client = MongoClient('mongodb://%s:%s@localhost:44898/?authMechanism=DEFAULT&authSource=AAC' % (username, password))
        self.database = self.client['AAC']
        
    #Complete this create method to implement C in CRUD
    #FIX NEEDED: For some reason when a variable is used to create an entry, that variable is updated to include the new object id
    def create(self, data):
        if data is not None:
            return bool(self.database.animals.insert(data)) #data should be a dictionary
        else:
            print("Nothing to save, because data parameter is empty")
            return False
       
            
    #Method to implement R in CRUD
    #This method returns a cursor object, to read actual entries the user must iterate through the docs using a for loop
    def read(self, data):
        if data is not None:
            return self.database.animals.find(data, {"_id": False}) #data should be a dictionary
        else:
            print("Nothing to find because data parameter is empty")
            return False
        
   #Method to implement U in CRUD
    #this method uses find to create a list of the objects matching data, it updates and returns the first entry found using the find function in Mongo
    def update(self, data, update):
        if data is not None: 
            result = self.database.animals.update_one(data, {"$set": update})
            results = []
            returnObject = self.database.animals.find(data)
            for doc in returnObject:
                results.append(doc)
            return results[0]
        else: 
            print("Nothing to update because data parameter is empty")
            return False
        
    #Medthod to implement D in CRUD
    #this method returns the document that was deleted
    # this method works by using find to generate alist of the documents, and returns the first object in the list which will be the object that is deleted - delete one deletes the first entry found
    def delete(self, data):
        if data is not None:
            returnObject = self.database.animals.find(data)
            results = []
            for doc in returnObject:
                results.append(doc)
            self.database.animals.delete_one(data)
            return results[0]
        else:
            print("Nothing to delete because data parameter is empty")
            return False
        