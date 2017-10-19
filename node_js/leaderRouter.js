//leader router module
var leaderRouter;

function module_initialization(express, bodyParser)
{
    leaderRouter = express.Router();

    leaderRouter.use(bodyParser.json());

    leaderRouter.route('/')
    .all(function(req,res,next) {
          res.writeHead(200, { 'Content-Type': 'text/plain' });
          next();
    })

    .get(function(req,res,next){
            res.end('Will send all the leaders to you!');
    })

    .post(function(req, res, next){
        res.end('Will add the leader: ' + req.body.name + ' with details: ' + req.body.description);    
    })

    .delete(function(req, res, next){
            res.end('Deleting all leaders');
    });

    leaderRouter.route('/:leaderId')
    .all(function(req,res,next) {
        if (req.method == 'POST') {
            res.writeHead(405, { 'Content-Type': 'text/plain' });
        } else {
            res.writeHead(200, { 'Content-Type': 'text/plain' });
        }
        next();
    })

    .get(function(req,res,next){
            res.end('Will send details of the leader: ' + req.params.leaderId +' to you!');
    })

    .put(function(req, res, next){
            res.write('Updating the leader: ' + req.params.leaderId + '\n');
        res.end('Will update the leader: ' + req.body.name + 
                ' with details: ' + req.body.description);
    })

    .delete(function(req, res, next){
            res.end('Deleting leader: ' + req.params.leaderId);
    })
    
    .post(function(req, res, next){
        res.end('Post is not supported for ' + req.params.leaderId);
    });
    
    return leaderRouter;
}

exports.leaderRouter = function (express, bodyParser) {
        return module_initialization(express, bodyParser);
}