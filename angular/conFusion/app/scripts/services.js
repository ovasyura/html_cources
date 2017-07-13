'use strict';

angular.module('confusionApp')
    .constant("baseUrl", "http://localhost:3000/")
    .service('menuFactory', ['$resource', 'baseUrl',
        function($resource, baseUrl) {
    
                    this.getDishes = function() {
                        return $resource(baseUrl + "dishes/:id", null, {'update':{method:'PUT'}});
                    };
                    
                // implement a function named getPromotion
                // that returns a selected promotion.
                    this.getPromotions = function() {
                        return $resource(baseUrl + "promotions/:id", null, {'update':{method:'PUT'}});
                    }
                    
    }])
    .service('corporateFactory', ['$resource', 'baseUrl', 
             function($resource, baseUrl) {
    
            this.getLeaders = function() {
                return $resource(baseUrl + "leadership/:id", null, {'update':{method:'PUT'}});
            };
    }])
    .service('feedbackFactory', ['$resource', 'baseUrl', 
             function($resource, baseUrl) {
    
            this.getFeedback = function() {
                return $resource(baseUrl + "feedback/:id", null, {'save':{method:'POST'}});
            };
    }])
;