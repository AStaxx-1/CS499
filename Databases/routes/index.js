var express = require('express');
var router = express.Router();

/* GET home page. */
router.get('/', function(req, res, next) {
  res.render('index', { title: 'Strack Milestone Four' });
});


/*GET Booklist page. */
router.get('/booklist', function(req, res) {
    var db = req.db;
    var collection = db.get('Angel');
    collection.find({},{},function(e,docs){
        res.render('booklist', {
            "booklist" : docs
        });
    });
});

/*GET New Book Page */
router.get('/newbook', function(req, res){
    res.render('newbook', {title: ' Add New Book'});
});

/*POST to Add Book Service*/
router.post('/addbook', function(req,res){
    //set our internal db variable
    var db = req.db;
    
    //get form values
    var bookTitle = req.body.BookTitle;
    var bookAuthor = req.body.BookAuthor
    var Type = req.body.Type;
    var Condition = req.body.Condition;
    var Remarks = req.body.Remarks;
    
    //set the collection
    var collection = db.get('Angel');
    
    //submit to the database
    collection.insert({
        "BookTitle" : bookTitle, 
        "BookAuthor" : bookAuthor,
        "Type" : Type,
        "Condition" : Condition,
        "Remarks" : Remarks
    }, function(err, doc){
        if(err){
            //if it fails return error
            res.send("There was an issue adding the book to the database");
        }
        else{
            //forward to the success page
            res.redirect("booklist");
        }
    });
});

module.exports = router;
