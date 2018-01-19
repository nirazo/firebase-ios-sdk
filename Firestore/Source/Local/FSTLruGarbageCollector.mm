#import <memory>
#import <queue>
#import "Firestore/Source/Local/FSTLruGarbageCollector.h"

#import "Firestore/Source/Local/FSTQueryCache.h"
#import "Firestore/Source/Local/FSTQueryData.h"

using std::priority_queue;

class RollingSequenceNumberBuffer {
 public:
  RollingSequenceNumberBuffer(NSUInteger max_elements) : max_elements_(max_elements) {
    queue_ = std::make_unique<priority_queue<FSTListenSequenceNumber> >();
  }

  void AddElement(FSTListenSequenceNumber sequence_number) {
    if (queue_->size() < max_elements_) {
      queue_->push(sequence_number);
    } else {
      FSTListenSequenceNumber highestValue = queue_->top();
      if (sequence_number < highestValue) {
        queue_->pop();
        queue_->push(sequence_number);
      }
    }
  }

  FSTListenSequenceNumber max_value() const {
    return queue_->top();
  }

  std::size_t size() const {
    return queue_->size();
  }

 private:
  std::unique_ptr<priority_queue<FSTListenSequenceNumber> > queue_;
  const NSUInteger max_elements_;
};

@interface FSTLruGarbageCollector ()

@property (nonatomic, strong, readonly) id <FSTQueryCache> queryCache;

@end

@implementation FSTLruGarbageCollector {
}

- (instancetype)initWithQueryCache:(id <FSTQueryCache>)queryCache {
  self = [super init];
  if (self) {
    _queryCache = queryCache;
  }
  return self;
}

- (NSUInteger)queryCountForPercentile:(NSUInteger)percentile {
  NSUInteger totalCount = [self.queryCache count];
  NSUInteger setSize = (NSUInteger)((percentile / 100.0f) * totalCount);
  return setSize;
}

- (FSTListenSequenceNumber)sequenceNumberForQueryCount:(NSUInteger)queryCount {
  if (queryCount == 0) {
    return kFSTListenSequenceNumberInvalid;
  }
  __block RollingSequenceNumberBuffer buffer(queryCount);
  [self.queryCache enumerateQueryDataUsingBlock:^(FSTQueryData *queryData, BOOL *stop){
    buffer.AddElement(queryData.sequenceNumber);
  }];
  return buffer.max_value();
}

@end