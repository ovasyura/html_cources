//promotion router module
var promotionRouter;

function module_initialization(express, bodyParser)
{
    promotionRouter = express.Router();

    promotionRouter.use(bodyParser.json());

    promotionRouter.route('/')
    .all(function(req,res,next) {
          res.writeHead(200, { 'Content-Type': 'text/plain' });
          next();
    })

    .get(function(req,res,next){
            res.end('Will send all the promotions to you!');
    })

    .post(function(req, res, next){
        res.end('Will add the promotion: ' + req.body.name + ' with details: ' + req.body.description);    
    })

    .delete(function(req, res, next){
            res.end('Deleting all promotions');
    });

    promotionRouter.route('/:promotionId')
    .all(function(req,res,next) {
        if (req.method == 'POST') {
            res.writeHead(405, { 'Content-Type': 'text/plain' });
        } else {
            res.writeHead(200, { 'Content-Type': 'text/plain' });
        }
        next();
    })

    .get(function(req,res,next){
            res.end('Will send details of the promotion: ' + req.params.promotionId +' to you!');
    })

    .put(function(req, res, next){
            res.write('Updating the promotion: ' + req.params.promotionId + '\n');
        res.end('Will update the promotion: ' + req.body.name + 
                ' with details: ' + req.body.description);
    })

    .delete(function(req, res, next){
            res.end('Deleting promotion: ' + req.params.promotionId);
    })
    
    .post(function(req, res, next){
        res.end('Post is not supported for ' + req.params.promotionId);
    });
    
    return promotionRouter;
}

exports.promoRouter = function (express, bodyParser) {
        return module_initialization(express, bodyParser);
}