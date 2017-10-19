//dish router module
function module_initialization(express, bodyParser)
{
    var dishRouter = express.Router();
    dishRouter.use(bodyParser.json());

    dishRouter.route('/')
    .all(function(req,res,next) {
          res.writeHead(200, { 'Content-Type': 'text/plain' });
          next();
    })

    .get(function(req,res,next){
            res.end('Will send all the dishes to you!');
    })

    .post(function(req, res, next){
        res.end('Will add the dish: ' + req.body.name + ' with details: ' + req.body.description);    
    })

    .delete(function(req, res, next){
            res.end('Deleting all dishes');
    });

    dishRouter.route('/:dishId')
    .all(function(req,res,next) {
        if (req.method == 'POST') {
            res.writeHead(405, { 'Content-Type': 'text/plain' });
        } else {
            res.writeHead(200, { 'Content-Type': 'text/plain' });
        }
        next();
    })

    .get(function(req,res,next){
            res.end('Will send details of the dish: ' + req.params.dishId +' to you!');
    })

    .put(function(req, res, next){
            res.write('Updating the dish: ' + req.params.dishId + '\n');
        res.end('Will update the dish: ' + req.body.name + 
                ' with details: ' + req.body.description);
    })

    .delete(function(req, res, next){
            res.end('Deleting dish: ' + req.params.dishId);
    })
    
    .post(function(req, res, next){
        res.end('Post is not supported for ' + req.params.dishId);
    });
    
    return dishRouter;
}

exports.dishRouter = function (express, bodyParser) {
    return module_initialization(express, bodyParser);
}
